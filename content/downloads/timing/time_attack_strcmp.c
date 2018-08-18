/*
 * Time attack proof of concept / tutorial.
 *
 * Author: Joakim Bech <joakim.bech@gmail.com>
 * Date: 2014-02-02
 */
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define TEST_LOOPS 1

#ifdef DEBUG
#define dprintf printf
#else
#define dprintf
#endif

/*
 * strcmp taken from from glibc 2.13, just for reference.
 * Compare S1 and S2, returning less than, equal to or
 * greater than zero if S1 is lexicographically less than,
 *  equal to or greater than S2.
 */
static int strcmp2(p1, p2)
	const char *p1;
	const char *p2;
{
	const unsigned char *s1 = (const unsigned char *) p1;
	const unsigned char *s2 = (const unsigned char *) p2;
	unsigned char c1, c2;

	do
	{
		c1 = (unsigned char) *s1++;
		c2 = (unsigned char) *s2++;
		if (c1 == '\0')
			return c1 - c2;
	}
	while (c1 == c2);

	return c1 - c2;
}

/*
 * Change "strcmp2" to some other comparing function that you want to test.
 */
static bool compare_strings(char* str1, char* str2)
{
	return strcmp2(str1, str2) == 0;
}

/*
 * A wrapper for the cpu instruction rdtsc, which stores the current cycle
 * number as a 64 bit number. The cpuid instruction is included because it
 * forces inorder execution. (See the 1997 Intel document on using rdtsc for
 * performance testing cited in the bibliography).
 * Grabbed from password.c by Dan Halperin (which also is a time attack proof
 * of concept).
 *
 * Be aware that rdtsc isn't reliable on a multicore system and power management
 * features have also made it even more inaccurate. However it works quite good
 * for the purpose of this demonstration.
 */
static inline uint64_t read_rdtsc(void)
{
	uint64_t d;
	__asm__ __volatile__ ("cpuid \n rdtsc" : "=A" (d));
	return d;
}

/*
 * Function that calculates the average time it takes to make TEST_LOOPS string
 * comparisons.
 */
static uint64_t do_stat(char *pw_ref, char *test_pw, char *test_str)
{
	uint64_t time_long = 0;
	uint64_t start = 0;
	uint64_t end = 0;
	uint64_t i = 0;

	for (i = 0; i < TEST_LOOPS; i++)
	{
		start = read_rdtsc();
		compare_strings(test_pw, pw_ref);
		end = read_rdtsc();
		time_long += (end - start);
	}

	if (test_str)
		printf("%s: %llu\n", test_str, time_long / i);

	return time_long / i;
}

/*
 * Function that makes a time attack on a provided password. I takes the correct
 * password, then it try to guess the correct letters in this provided password
 * one by one by calling a string compare function. Since the standard string
 * compare (strcmp) function is linear in time when it comes to find the correct
 * answer you can make fairly good guess to find the correct letter. This since
 * the correct letter will have slightly longer execution time compared to the
 * ones with incorrect letters. Therefore loop over a-z and store the letter
 * that had longest running time when doing string compare. Repeat this for all
 * letters and then finally do a full string comparison to see whether we
 * guessed correct or not.
 */
bool time_attack_pw(char *correct_pw)
{
	bool result = false;
	char current_char;
	int i = 0;
	int j = 0;
	uint64_t current_time = 0;
	uint64_t max_time_found = 0;
	char *calculated_string = calloc(strlen(correct_pw) + 1, sizeof(char));
	calculated_string[strlen(calculated_string)] = '\0';

	/* FIXME, why do we need to cut away one? rdtsc inaccuracy? */
	for (i = 0; i < strlen(correct_pw) - 1; i++)
	{
		max_time_found = 0;
		for (j = 'a'; j <= 'z'; j++)
		{
			current_char = j;
			current_time =
				do_stat(correct_pw + i, &current_char, NULL);

			if (current_time > max_time_found)
			{
				max_time_found = current_time;
				/*
				 * Store the letter that gave longest the
				 * response time for letter X in position i in
				 * the array where we store all guesses.
				 */
				calculated_string[i] = j;
			}
		}
	}
	dprintf("Guessed that pw should be: %s\n", calculated_string);
	/*
	 * Check if the provided string completely matches the calculated
	 * string. Ignore the last space, see FIXME above.
	 */
	result = strncmp(correct_pw, calculated_string,
			 strlen(correct_pw) - 1) == 0;
	free(calculated_string);

	return result;
}

int main(int argc, char *argv[])
{
	int i = 0;
	int correct_guesses = 0;
	/*
	 * FIXME, last char gives strange values, we add a space here, and strip
	 * it away in the time_attack_pw function. I suspect inaccurate rdtsc
	 * instruction.
	 */
	char* long_string = "thisisalongstring ";
	char* short_string = "foo";

	printf("%s\n", "Shows a couple of examples of the time it takes to make string comparison");
	(void)do_stat(long_string, long_string, "avg time long string (thisisalongstring)");
	(void)do_stat(short_string, short_string, "avg time short string (foo)");
	(void)do_stat(short_string, "XXX", "avg time 0 char correct (XXX/foo)");
	(void)do_stat(short_string, "fXX", "avg time 1 char correct (fXX/foo)");
	(void)do_stat(short_string, "foX", "avg time 2 char correct (foX/foo)");
	(void)do_stat(short_string, "foo", "avg time 3 char correct (foo/foo)");

	if (argc > 1)
	{
		for (i = 0; i < atoi(argv[1]); i++)
		{
			if (time_attack_pw(long_string))
				correct_guesses++;
		}
		printf("%d successful timing attacks\n", correct_guesses);
	}

	return 0;
}
