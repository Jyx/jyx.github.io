---
title: ATschjoo
date: 2013-12-22 00:04
comments: true
status: hidden
authors: Joakim Bech
modified: 2018-08-18
---
During my ~2.5 years at Sony Ericsson I worked most of the time with AT
commands. You maybe remember those commands from late -80 / early -90? You
could change baud rate, etc etc on your 9600, 14.4 28.8 modem. Could anybody
still use these? Oh yes, the AT commands are still used a lot in mobile phones.
In principle you could achieve the same things using AT commands as you could
do by sitting and holding the phone in your hand (actually when thinking I
believe that you can do more).

Accessories use AT commands a lot, for example portable handsfree and a lot of
other gadgets that you can connect to your phone in any way, cable, Bluetooth,
IrDA.

So what is ATschjoo? As you probably understand it has something to do with AT
commands. It’s a tool where the user can send AT commands and receive the
response from them. Think of it like the
[hyperterminal](http://www.hilgraeve.com/hyperterminal.html) that has been
shipped with all Windows versions (except Windows 7), but this is a little bit
more useful. It’s actually one of the reasons why I wrote this. Most of the
people at work seemed to use hyperterminal. But I got tired of copy pasting or
writing AT commands a zillion times.

Unfortunately usual I didn’t got any spare time on work to code something like
this, so I had to do it on my spare time at home and therefore it’s only half
finished as many of my projects (I always have many projects and ideas). But
still it was working quite good and according to people I know at Sony Ericsson
it is still in use there.

## Features?
Finished features are:

* A drop down with available COM-ports – This might sound silly, but a lot of
  terminal programs out there shows only `COM1` to `COM4`. Some shows a big
  list of a big range and so on. ATschjoo shows only the available ports.
* Auto complete list – In ATschjoo you can store commands in a file
 (autocomplete.txt) which would be used in auto-completion when typing commands.
  This list can also be used to populate the command window.
* Character counter – When you want to test limits you want to now how many
  character you send. Nothing fancy, but very handy.
* Loop mode – When you want to test a bunch of AT commands over and over you
  can tick a check box so the command you have entered will be called one by one
  over and over again.
* Delay – You can set the delay between the commands sent.

Planned features were:

* Logging window – A window where you could log traffic on another port.
* Syntax highlight support – The idea was that you should be able to setup
  syntax highlighting based on regular expressions, so that you could filter out
  response messages easily.
* Integrate it to the phone emulator at work – Since I did all development on
  ATschjoo at home I couldn’t really test this, therefore this feature was put
  into a sealed box.

## Screenshots
The first version looked like this.

<img alt="ATschjoo first version" src="{filename}/images/atschjoo/atschjoo_old.png" width="760">

And the last version I did looked like this:

<img alt="ATschjoo current version" src="{filename}/images/atschjoo/atschjoo.png" width="760">

## Further work on ATschjoo?
Do I plan to do more work on ATschjoo? No I don’t. Sure there is a need for a
program like this, but doing terminal program isn’t high up in my prio list for
the moment. But! if you are a programmer and want to make some money then start
code something like this. There isn’t many good tools for this out there and
demonstrate it for companies. Don’t think that they have much better in-house
tools. That is not the case most of the time I guess.

## Language: C# (using .NET framework 2.0)
Status: Main features is working, but there are still quite much to do to get
this in a good shape. I remeber that there was some bug that caused the program
to hang if you didn’t disconnect before remove the USB cable for example.

## Binaries:
* [ATschjoo](/downloads/atschjoo/ATschjoo.exe) (SHA1: 391285b7c0b24f752573b1fb93cde62a39766c4d)
* [(oldest)](/downloads/atschjoo/ATschjoo_old1.exe) (SHA1: 9e97d13349855024b9ce38b43680956be646ae94)
