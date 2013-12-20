---
layout: post
title: "What about Total Commander?"
date: 2010-03-12 00:06:26 +0100
comments: true
categories: [Tools]
---
{% img right /images/totcmd/logo_tc.jpg %}
As my first post on my new site I'll start by talking about Total Commander. I
have been using this wonderful tools since I think I got my first PC. Back then
it was called Windows Commander. So what is it that makes this tool so
wonderful?
<!-- more -->
Well, if you just install it and start it you maybe won't be that
impressed. It has a quite old and perhaps boring look. But, if I can choose
between good looking tool without any features (Windows Explorer) and a not so
good looking tool with almost any features you can think of that is needed or
could be nice to have when it comes to file handling on a computer. Then I
choose the latter one. Which, in this case is Total Commander.

So, what do you normally do with your files on your computer? For a normal user
you open files and maybe move files. That might be it for a big part of the
population. But if you are a slightly more advanced user? Then you might need to
duplicate files, pack/unpack files. You maybe want to filter the files so you
only will se files matching a certain pattern. You maybe want to synchronize
your files on a backup drive? Want to syntax hi-light files with certain name?
Copy file names with or without full path to clipboard? All of this and much
more you can do with Total Commander and as a good bonus there are quite easy
keyboard shortcuts for doing that. So you don't have to move one of you hands
between the keyboard and the mouse all the time.

### The look
Total Commander is  composed as one main window with a split pane. First time I
saw this was back in time when Amiga 500 was a popular computer. I'm thinking of
the file manager [Directory Opus](http://en.wikipedia.org/wiki/Directory_Opus).
Is this a good or a bad thing? Well, since it still exists and seems to be quite
popular among people that have some higher demand on file exploring tool than
the average user have, then I think we can say, yes it's a good thing. To be
honest it's actually very good. You have two panes open all the time within the
same program, so you can very easy move, copy files etc. Since quite some time
ago Total Commander also supports tabs. Hence you can have multiple tabs for
both panes. You jump between the panes by simply pressing TAB and you jump
between tabs in the panes by pressing CTRL + TAB.

### Renaming on steroids
There's something called Multi-Rename Tool in Total Commander which is quite
handy. It can rename a lot of files for you in very few clicks. Imagine you have
a folder with following files:
	a_foo.zip
	b_foo.zip
	c_foo.zip

Now you wan't to rename those to:
	01_a.zip
	02_b.zip
	03_c.zip

In Total Commander you simply mark the files and press CTRL + M and the
Multi-Rename Tool will launch. In this particular example you prepend the
"Rename mask: file name" with "01\_" and in the "Search & Replace" you write
"\_foo" in the "Search For", like shown in the screenshot below.

{% img /images/totcmd/tc_multi_rename_tool.png %}

You can just imaging how helpful this is when you are renaming a couple of
hundred jpg files taken with your digital camera where you often have quite
cryptic naming as default.

### Shortcuts and some more features
I could explain a bunch of features like the Multi-Rename Tool in detail. But
some features are very simple to use, so I list a couple of my daily things I do
using Total Commander.

Let's say you have c:\a in the left pane and c:\b in the right pane.

Mark files? Use space or SHIFT + PgUp/PgDown or CTRL + plus or simply press plus
and make a filter out the files.

Want to move files from folder a to b? Mark the files you want to move and press
F6.

Rename a file? SHIFT + F6. This is a bit odd, since most other program have F2
as rename button.

Pack files? Mark the files, ALT + F5, then ENTER. Files are now packed and put
into the folder on the other pane.

Unpack files? Mark the files, ALT + F9 then ENTER. Files are unpacked to the
other pane.

Browse packed files? Simply press ENTER on a zip file for example and you will
see the content immediately without unpacking it. Very useful! Note that you can
copy single files when in this state. This is also very useful.

Find files? Alt + F7, then just search. Note the "Search subdirectories" which
is very useful of you have a big project with a lot of subfolder but you know
that the file you are searching is not that deep down into the folder structure.
Then you use this to select how many subdirectories you want to traverse. Very
useful, especially in combination with the "Find text" in the same window.

Go to folders that you have been in? Press ALT + down and you get a neat list
for the last ~30 folders you have been in. Note that this is unique for the
pane. I.e. one for the left pane and one for the right pane.

Run a command? Just type it and press ENTER. For example I want command prompt.
I simply type "cmd" then press enter. Voila I get a command prompt which have
the path same to my current folder in my pane.

Mark a folder as favorite? Press CTRL + d then a. Type any name you like to
refer to this folder.

Go to a favorite folder? Press CTRL + d and select your favorite folder.

Do a mouse right click? Press SHIFT + F10.

View content of a file? Press F3.

Edit a file? Press F4.

### Should you buy Total Commander?
Well, at least download it asap and start using it. If you just want to try it,
you will only get one(!) nag screen when starting the program. Then you can
leave it running for hours, days, weeks, years with full functionality and no
more nag screens. But, when you notice that you cannot really live without this
tool, then I think you should register the program. Christian Ghisler (the
author) deserves money for this great tool and he has given free updates since I
registered it, which was quite long time ago. As the headline says, I think
Microsoft should buy this tool/company and replace Windows Explorer with Total
Commander. Thanks!

Link to the official site: http://www.ghisler.com/
