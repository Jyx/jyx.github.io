---
layout: post
title: "Apply patches in Git"
date: 2012-03-09 00:16:48 +0100
comments: true
categories: [git, coding]
---
{% img right /images/git/logo_git.gif %}
One common task that a developer has to do sooner or later is to apply a patch
in Git. I have a simple scheme that I've been using for a long time and it is
very seldom that I get into problem nowadays when I'm doing patch work.
<!-- more -->

###The short version for the impatient
{% codeblock lang:bash %}
$ git am < my_new_feature.patch
$ git apply --reject --whitespace=fix my_new_feature.patch
$ git status
$ vim my_conflicting_file.c*
$ find . -name "*.rej" -exec rm -f {} \;
$ git add .
$ git am --resolved
{% endcodeblock %}

###Long version for the one needing explanations to the steps
To start with I always first try applying the patch with git am, i.e.
	$ git am < my_new_feature.patch

Sometimes this is enough and the patch simply applies, however when it fails to
apply I just continue writing.
	$ git apply --reject --whitespace=fix my_new_feature.patch

This will force Git to apply as much as it can and for the rest of the hunks
that it cannot merge it will produce files ending with .rej. So the next step I
do after git apply is just to run
	$ git status

And notice the untracked files ending in .rej. Now I know what files Git
couldn't merge when applying the patch, so let's say that I have a file called
my_conflicting_file.c which Git couldn't merge. To solve this I open it in my
favorite editor by doing like this:
	$ vim my_conflicting_file.c*

This will open both my_conflicting_file.c and my_conflicting_file.c.rej. I will
split the window in vim (CTRL+W V), and then open the other file by typing :bp
in vim. Now it is up to you as a developer to decicde what changes in the *.rej
file should go into the conflicting file. I.e, what changes in
my_conflicting_file.c.rej, should be in my_conflicting_file.c. Sometimes you
will notice that you don't have to change anything at all and sometimes you will
notice that you have to add or remove lines in the conflicting file. Don't
forget to remove the + and/or - at the start of the lines in the *.rej file!
When this step is done I delete all the *.rej files and then add the changes
files to the index in Git. I.e:
	$ find . -name "*.rej" -exec rm -f {} \;
	$ git add .

The last step you have to do before the patch have been merged is to tell git
that the "am" that you started have been resolved.
	$ git am --resolved

Patch work done! If you follow this scheme I'm pretty sure that you will do fine
in the future when applying patches.
