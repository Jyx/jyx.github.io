---
layout: post
title: Timing Attack - Proof of Concept
date: 2014-02-02 10:38:37
comments: true
category: Hacking
authors:Joakim Bech
modified: 2018-08-18
---
You might have heard about timing attacks, but either thought it sounded
too complicated to understand or that it is too complicated to actually do such
an attack. In this post I'm going to give a brief overview of a timing attack
and also provide some example code that you can play with on your own. Hopefully
after reading this post you will understand that you cannot neglect this if you
are creating a system where security is needed.

# What is a timing attack
A [timing attack](http://en.wikipedia.org/wiki/Timing_attack) is a so called
[side channel attack](http://en.wikipedia.org/wiki/Side_channel_attack)
where you analyze the timing information on a system is such a way that it
allows to break the protection of the system or a program running on it.

# How is a timing attack performed?
Typically you need to measure the amount of time needed to do operations of some
kind. You can do this in several ways, for example you could hook up a set of
probes on a chip or a PCB and watch the result on an oscilloscope or a logical
analyzer. Another option is to simply leverage features from the
CPU/architecture itself. On a normal PC running Intel (or AMD) you can use the
time stamp counter [rdtsc](http://en.wikipedia.org/wiki/Time_Stamp_Counter)
or a High Precision Event Timer
[hpet](http://en.wikipedia.org/wiki/High_Precision_Event_Timer). Be aware that
the time stamp counter isn't reliable any longer, since process speeds can
change (due to power management), you have context switches etc. But just for
testing it can be good enough.

So you have found a way of taking time measures, what next? The easy answer is,
start measure the execution time of sensitive functions. For example when
calling functions that verifies password, functions that does encryption and
such. Measuring the time needed for `strcmp` as exemplified in the proof of
concept code below is easy. It becomes more complicated if you want to do the
same when doing
[AES](http://en.wikipedia.org/wiki/Advanced_Encryption_Standard#Side-channel_attacks)
encryption for example. It is still doable, but you also need to know the
algorithm to know where to look and how to interpret the leaked information.

# Countermeasures
Main idea is that you need balance the string compare functions so that it
always takes the same amount of time to perform.

# Proof of concept
I have put together a small proof of concept / testing program to show that it
is actually not that complicated to do a timing attack. It is unlikely that it
is as easy as this, but still, it gives the idea and shows that you can
actually use timing to guess password, guesses that are fairly good. The main
idea is to show how execution time actually varies when doing string
comparison. The by using this information leakage we show that we can guess
pretty good what we believe the correct character is in the correct
password/string.

# The algorithm

1. Loop over all characters, one by one in the string that we want to check
   (`thisisalongstring` in this case).

2. For every character in the string, do an inner loop, where you are looping
   from `'a'` to `'z'`. For every call to the string comparison function record
   the amount of time it took. The letter that had longest execution time is
   most likely the correct character. Hence save that character in the in the
   array that contains guessed character.

3. Lastly compare the correct string with guessed string to see if we got all
   timing based guesses correct or not.

## Results
Here are the test result of a test run with debug information enabled
```bash
$ make DEBUG=1
$ ./main 10
Shows a couple of examples of the time it takes to make string comparison
avg time long string (thisisalongstring): 821
avg time short string (foo): 532
avg time 0 char correct (XXX/foo): 486
avg time 1 char correct (fXX/foo): 495
avg time 2 char correct (foX/foo): 540
avg time 3 char correct (foo/foo): 561
Guessed that pw should be: thisisalongshring
Guessed that pw should be: thisisalongstring
Guessed that pw should be: thisisalongstring
Guessed that pw should be: thhbisalongstring
Guessed that pw should be: thisisalongstring
Guessed that pw should be: thisisalongstring
Guessed that pw should be: thisisalongstring
Guessed that pw should be: thisisalongstring
Guessed that pw should be: thisimalongstrimf
Guessed that pw should be: thisisalongstrhng
6 successful timing attacks
```
The figures will vary, but they are almost always in the same region. Looking
at:

**Line 3**: we can see that it takes `821` time units for a full and correct string
compare of the string `thisisalongstring`.

**Line 4**: we can see that it takes `532` time units to correctly match the
string `foo`.

**Line 5-8**: for every test run, we add a correct matching character and as
expected we can see that the time increases for every correct character. This
is because the string compare function as said before has a timing linear to
the correct number of characters.

**Line 9-19**: shows the result when trying to guess the string
`thisisalongstring` based on the time it takes to guess `'a'`, `'b'`, `'c'`,
... `'z'`, for every character. This particular run we guessed correct 6 out or
10 times. Not that bad, it takes roughly 0.002 seconds to run everything above.
According to Steve Gibson's [Password Haystack](https://www.grc.com/haystack.htm)
page, it takes approximately 3.75 centuries to brute force that password
**once** using a what he calls a "massive cracking array scenario (assuming one
hundred trillion guesses per second)".

# A couple of interesting things I've noticed

* If I increase the `TEST_LOOPS` define I actually get much worse result?
* If I turn on all optimizations, i.e. `-O3`, it doesn't work at all.
* The last character was always incorrectly guessed and that is the reason why
  I've added a space at the end of the string '`thisisalongstring `', which I
  later on strip away. I believe the reason for this problem is inaccuracy
  using `rdtsc`.

If any reader of this post knows the answer to my reflections above, please
leave a comment.

# Source code
* [time_attack_strcmp.c](/downloads/timing/time_attack_strcmp.c)
* [Makefile](/downloads/timing/Makefile)
