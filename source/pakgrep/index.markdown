---
layout: page
title: "Pakgrep"
date: 2013-12-22 22:23
comments: true
sharing: true
footer: true
---
### What is pakgrep?
Pakgrep is a program that allows you to extract files from a Quake2 pak-file.
For you that doesn't know what a pak-file is you could compare them with
zip-files but for the game Quake2 instead. I.e. the pak files contains textures
for game levels, skins for the models, sound for your models and maps. I could
contain config files and background picture when showing the console. Pakgrep
is written in C and supports [regular expressions](http://en.wikipedia.org/wiki/Regular_expression) as search string.

### Why pakgrep?
During all the years I played Quake2 I created a pak-file for myself which
contained all goodies that I liked. I had nice textures, good sounds and our
own ergo Gibbus background and a text font that I really liked. One day when I
was re-installing Windows I did a mistake deleted my Quake2 folder by mistake.
Not a big deal I thought until I realized that my pak-file was missing. I had a
lot of pak-files backed up, but not my own. However it should be possible for
me to recreate it again by copy and paste files from other pak-files. But to do
that you had to open/extract every single pak-file, browse the extracted files
and then decide if it was the file you were looking for. A quite time consuming
task. I especially wanted to find the conchars.pcx file which contains the font
showed in the game. I decided to create a small program that could extract the
files and this is what it ended up with, i.e. pakgrep.

### How to use it
1. It is made for Windows and I have used it on WinXP (32) and Windows (64).
2. Copy pakgrep.exe to a folder containing pak-files (*.pak).
3. Type pakgrep.exe files_to_search_for pakfile.pak.

For example to search for and extract conchars.pcx files from pak9.pak you could write:
	pakgrep.exe conc* pak9.pak

On the pakfile I tried when writing this I got the following result
	c:\pakgrep>pakgrep.exe conc* pak9.pak
	Pakgrep v1.0 by Joakim Bech
	
	Extracting: pics/conback.pcx
	Extracting: pics/conchars.pcx

I.e. the search string matched both conback.pcx and conchars.pcx.

### Download / info

**Language**: C

**Source**: Sorry, I will not publish source for this project.

**Binary**: [pakgrep.exe](/pakgrep/pakgrep.exe) (SHA1: 5c5150099d9e9d7d772ccb9b364a1267697f8463)
