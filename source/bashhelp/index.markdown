---
layout: page
title: "Bash Help"
date: 2013-12-21 22:45
comments: true
sharing: true
footer: true
---
This is nothing fancy, it’s just a simple bash-script itself that prints the
syntax of commands that I use quite often. So it is quite neat to just clone
this and put into my PATH, so regardless of which folder I’m currently standing
in I simply type bhelp command to get the syntax of that particular command.

You find a link to the script in the sidebar to the right under the GitHub
Repos sections.

A sample of the output from the script could look like this:

{% codeblock lang:bash %}
$ bhelp gpg

gpg
================================================================================
gpg --gen-key                                   Create a keypair
gpg --list-keys                                 List all keys
gpg --import tmp/gnupg/secring.gpg              Import keyring
gpg --import my_friends_key.asc                 Import ASCII key
gpg --edit-key joakim                           Edit key "joakim"
gpg --armor --export 060AB907 > joakimbech.asc  Create public key in ASCII
gpg -K                                          List all keys from secret
                                                keyring
gpg -e -r Joakim my_plaintext_file.txt          Encrypt a file using key Joakim
gpg -o plain.txt -d cipher.txt.gpg              Decrypt file cipher.txt to
                                                plain.txt
gpg -d cipher.txt.gpg                           Decrypt a file

gpg --verify foo.tar.gz.{asc|sig} foo.tar.gz    Verify signature of a file
gpg --armor --detach-sign foo.tar.gz            Create a detached signature
gpg --delete-key 'myfriend@his.isp.com'         Remove a key
gpg --delete-secret-key 'mysecretkey'           Remove a secret key

Change uid
  gpg --edit-key Joakim
    uid 2                                       Number of the email/uid
    primary
    save

Add uid
  gpg --edit-key Joakim
    adduid
    save

Delete uid
  gpg --edit-key Joakim
    deluid 2                                    Number of the email/uid
    save
================================================================================
{% endcodeblock %}
