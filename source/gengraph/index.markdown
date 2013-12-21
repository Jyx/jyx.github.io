---
layout: page
title: "Gengraph"
date: 2013-12-22 00:19
comments: true
sharing: true
footer: true
---
Tool for generating dependency graphs between files and folder in C projects. I
started writing this program so I could bring it with me to work and there my
goal was to be able to find out dependencies between source code modules. I got
some quite nice graphs. But I cannot show them here due to security reasons.
After that I tried this on the Linux kernel. That didn’t work that good. The
Linux kernel have full path includes <linux/…> which we don’t have at work. So,
that is the major hassle with the current version.

Here is  a screenshot from the test data (which is included in the source at GitHub).

{% img /images/gengraph/mygraph_dot.png %}

**Language** : Perl

**Status**: Ongoing, still a bit buggy.

**Source**: http://github.com/Jyx/gengraph (link on the side bar)
