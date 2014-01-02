---
layout: page
title: "NIM and Squeezebox"
date: 2013-12-22 17:50
comments: true
sharing: true
footer: true
---
Don't most of us just dislike (to say it in a nice way) all those telephony
sellers, that want to sell you newspaper subscriptions, very nice insurances,
much better mobile subscriptions than the one you already have? Personally I
really like when they are calling a Friday at 19 o'clock on the evening just
when you have started to enjoy the weekend. No, as you already understand I
don't like it. A couple of months ago when a phone caller just had called me I
was beginning to think about how to stop this. I was surfing the net and found
a couple of different solutions for this. Everything from building the
electronics yourself to buying complete solutions. In the past I had also heard
about [Asterisk](http://www.asterisk.org/), but that sounded a bit complicated,
I wanted an easier solution.

One page that I liked was www.nim.se. They had nice little unit, simply called
nim. The nim will decode the DTMF signals to an ASCII string. I could also see
on the page that there were quite many scripts already written for the nim.
However most of the scripts was for Windows and I planned to use this on Linux
and not X86 Linux I planned to use it on my ARM-based QNAP TS-209 PROII (a NAS
which is running Linux under the hood). But I though if there isn't anything
that already is working, then I have a fun project in front of me.

So I ordered the unit and when I got it I must say that I was surprised how big
it was. Thinking about what it achieve it could be much smaller in size. I
first installed and tested it on a laptop with WinXP and it worked perfectly.
Then I wanted to try it on my QNAP. First problem, there is no COM port on the
QNAP! I had an USB to RS232 cable laying around so I connected the nim to the
QNAP using this cable. Result? Nothing happened. Why? There was no driver for
the cable which has a chip called PL2303 inside. I installed a cross compile
toolchain for ARM and downloaded source for this chip. I managed to compile the
driver for ARM and put the kernel driver on the QNAP and loaded it. I tried
with the USB to RS232 cable again and this time it worked. You can download the
required drivers here:

[pl2303_usb_arm.tar.gz](/nimbox/pl2303_usb_arm.tar.gz) (SHA1: 9d2f6ee563b4abfd533e0932356f3e9c340e1bf8)

And load the modules by typing
	insmod usbserial.ko
	insmod pl2303.ko


Second problem! I need a modem to be able to answer and hang up calls. The QNAP
have no integrated modem and I don't any modem laying around. So, what should I
then do with the nim without a modem? I surfed the nim forum and found out that
there is a software called YAC client which can show incoming calls on your
computers at home. I installed this on my computers. Now I had to get some kind
of server software to run (on Linux). I found a Perl script called Phoneserver
which is written by Jan Nilsson. I tested this Perl script and indeed it
worked. The calls showed up on my computer. Nice! But could I use it to
anything else? I have a [Squeezebox Classic](http://www.logitech.com/en-us/support/881?crid=409&osid=14&bit=64) at
home which I bought a couple of years ago. You can control the Squeezebox using
telnet (yes, this insecure protocol still exits). This simple BASH-script will
send the string you put as argument to the Squeezebox server, which in turns
sends it to the Squeezebox with a certain mac-address.

{% codeblock lang:c Send string to squeezebox %}
#!/bin/sh
MSG=$(echo $1|sed 's/ /%20/g')
(
echo 00:04:20:07:3d:00 show line2:$MSG font:huge centered:1 duration:4
sleep 1
echo exit
) | telnet 192.168.0.196 9090
exit
{% endcodeblock %}

So, now I had a working Perl script for the nim and a bash script that could send strings to the Squeezebox.

### Time to modify phoneserver.pl

I had to add some code to this Perl script so it showed the incoming calls on
the Squeezebox and that could handle the queries to hitta.se and eniro.se.
Since the calls to those two sites could take some time I decided to call the
Squeezebox twice. First time with the phonenumber (and name if the name is
already known). Next time a couple of seconds later after getting a response
from hitta.se or eniro.se I presented the number and whatever was found. I had
to add a thread to the Perl script which waits for messages meant to go to the
Squeezebox. I wrote the function send_sbmsg for this as below:

{% codeblock lang:perl Modified phoneserver.pl script %}
sub send_sbmsg {
    print "Thread started\n";
    my $DEBUG = 1;

    while (my $msg = $queue->dequeue()) {
        # Always send firsta message, i.e. phone number only.
        print "Number only: Popped $msg off the queue\n" if $DEBUG;
        my $sbmsg = "./sbmsg_short.sh \"$msg\"";
        print "$sbmsg\n" if $DEBUG;
        system($sbmsg);
        sleep 6;

        $semaphore->down();
        my $copy_numbersent = $numbersent;
        $semaphore->up();

        # Next check if we have name also, then we should resend that.
        if ($copy_numbersent == 2) {
            $msg = $queue->dequeue();
            print "Name also: Popped $msg off the queue\n" if $DEBUG;
            my $sbmsg = "./sbmsg.sh \"$msg\"";
            print "$sbmsg\n" if $DEBUG;
            system($sbmsg);
        } else { # Otherwise, send same message again.
            print "Resend Number only: $msg\n" if $DEBUG;
            my $sbmsg = "./sbmsg.sh \"$msg\"";
            print "$sbmsg\n" if $DEBUG;
            system($sbmsg);
        }

        $semaphore->down();
        $numbersent = 0;
        $semaphore->up();
    }
}
{% endcodeblock %}

These are the main changes made to the script. You can download the complete
script here (and don't forget to give Jan credits for the original version):

[phoneserver.tar.gz](/nimbox/phoneserver.tar.gz) (SHA1: 0c48e94aba48962bc1ad9caa8599b04bd0bcffc3)

### Demonstration

Below is a video clip showing it in action. I'm calling my home number from my
cellular and you can see that my name and number will show up on the
Squeezebox.

<iframe src="//player.vimeo.com/video/11017266" width="500" height="375" frameborder="0" webkitallowfullscreen mozallowfullscreen allowfullscreen></iframe>
