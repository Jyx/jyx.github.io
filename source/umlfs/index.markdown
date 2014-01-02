---
layout: page
title: "UML FS"
date: 2014-01-02 07:01
comments: true
sharing: true
footer: true
---
From time to time when I want to test things in the Linux kernel I use [User Mode Linux](http://user-mode-linux.sourceforge.net/)
which is a kind of virtual machine which allows you to run a Linux
kernel as a user mode process. To build user mode is simple, just run

	$ make ARCH=um

and you will get a binary to run UML. However you also need a filesystem and
that could be a bit tricky to setup. I’ve created a shell script which does
this for Ubuntu, Hardy Heron. This script will download a “debootstrap” of
hardy and then configure your filesystem so you can run apt-get. It will also
create some simple shell scripts, vimrc and put those on the filesystem so they
are ready to be run when setting up the files system and when UML has booted.
You are guided during the setup when running this script, so just follow the
instructions.

{% include_code umlfs/create_uml_fs.sh %}
