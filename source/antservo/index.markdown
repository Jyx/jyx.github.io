---
layout: page
title: "Antenna servo"
date: 2013-12-21 22:54
comments: true
sharing: true
footer: true
---
I bought an indoor antenna for DVB-T which is called [Televés Mira](http://www.kjell.com/sortiment/ljud-bild/tv-tillbehor/antenner-tillbehor/tv-antenner/campingantenner/televes-mira-p30117).  This antenna didn’t work so well for me. I had to put into the room next to the room where I have my TV, i.e. not very optimal to have it there with a long
antenna cable going between the rooms.  Another thing that I had problem with
when trying to adjust this antenna was that as soon as I was coming close to
the antenna it seems like I myself became part of the antenna and I get perfect
picture with good signal quality. But as soon as I let my hands off the Mira
and went three steps away the picture started to jump.

Then I realised that one of my neighbours told me that there is a tube for
cables already installed between the attic and our multimedia central in the
house. So I bought 15 meters of antenna cable and put this into the mentioned
tube. Now I had to solve the problem where I became antenna as soon as I
touched my Mira. I decided to buy a small servo which normally are used for RC
cars etc. The plan was that this servo should move the Mira. But, how do you
get the actual servo to move?

### Move a servo
A servo is controlled by PWM (Pulse Width Modulation). It’s not that
complicated as it might sound. At every 20 ms (50Hz) you need to create a pulse
which will move the arm of the servo. How it moves depends on the width of the
pulse. Normally it’s something between 0.5- to 2 ms.  I.e 0.5 ms might move the
arm to the leftmost position and 2 ms will move the arm to the right most
position. I found a cheap servo at dealextreme.com which I ordered, but when it
arrived I realised that it was very tiny and I couldn’t really use it for my
antenna. But still I wanted to fulfill this project.

### PIC16F690 and Microchips PicKit2 programmer
I started looking for information about other similar projects and found out
that a chip from Microchip called
[PIC16F690](http://www.microchip.com/wwwproducts/Devices.aspx?dDocName=en023112)
had an internal PWM. I thought that this sounded like a fun thing to try. Both
since I’m curious about building a this stuff and also since it could be fun
trying to code something in assembler which I haven’t done much at all I had to
admit. I went to [Elfa](https://www.elfa.se) in Malmö and bought a PicKit2
starter kit which is a programmer and also a small lab board which actually has
a 16F690 on it. After unpacking the unit and installing drivers I started to
briefly read the PDF’s that were included in the bundle.  Shortly after I found
the “low pin count demo” PDF which is a basic tutorial of the hardware and it
goes through most of the assembler instructions that exist for a PIC. The
lesson about A/D conversion (Analog/Digital) was quite handy I noticed later
on.

When I had gone through the low pin count demo lessons I started working on my
own small program. I quickly realised that I couldn’t use LED as indicator for
the signal, since it has to high frequency. I was scratching my head and was
thinking “do I really need to buy some kind of oscilloscope to be able to see
what is happening?” After reading more PicKit2 PDF I found out that the PicKit2
itself could actually be used as a logical analyzer. It has three channels for
this. So this was perfect, just what I needed. I connected the output signal to
the PicKit2′s logical input and the started the included tool for doing logical
analyse. Now I could easily follow the output signal.

###Electronics, a voltage divider as A/D signal
I found a very good blog article at ermicroblog which does basically the same
as I wanted to do. So I did basically the same thing, but instead of using two
LDRs (Light Dependant Resistor) with two inputs I only wanted to have a single
input which varies with the resistance from a potentiometer. The scheme is very
simple. It is called a voltage divider. I added a 14k resistor in serie with a
potentiometer, so when the potentiometer is 0 ohm you have some milliamps
flowing in the circuit.

	U = I * R => I = U/R => I = 5V / 14k = 0.3 milliamps.

When we are in this state their is no voltage over the potentiometer, hence the
input voltage to the A/D is zero. On the other hand, when you increase the
potentiometer you will get more and more voltage over the input to the A/D pin.
You remember the the formula?

	U = I * R => U1 = (I1 + R1) , U2 = (I2 + R2), U = U1 + U2.

This is the only few calculations you need to know to get this going. My
connection scheme looked like this (vridpott is a nickname for potentiometer in
Swedish).

### The result
The result was good enough, I can move the servo about ~180 degrees (90 degrees
CW/CCW). The assembler code is probably quite ugly, but I can live with it
since it is the first time I was writing assembler for PIC. I also had to tweak
the min/max values for the server by hard coding values that I found out by
trail and error using the PicKit2 logical analyzer. One thing that I stumbled
upon was when doing A/D conversion. The resolution for the A/D conversion in
the PIC16F690 is 10 bits, i.e 0-1023. But, how do you handle that since your
variables in PIC assembler has max value of 255. I cheated, I just skipped the
two least significant bits leaving me with a resolution of 0-255 from the A/D
conversion. This should be enough since I expected the servo to only turn about
180 degrees.

I have created a video clip showing it running, you can find it [here](/antservo/servo.wmv) (WMV 8.1 MB).

And below is a screenshot which shows the logical analyzer in the background on the monitor.
{% img /images/antservo/logical_analyser.jpg %}

### Source
Source code is [here](/antservo/servo.zip)
