---
layout: post
title: Fetchmail and GnuPG
date: 2014-11-01 23:02:03
comments: true
category: Coding
authors:Joakim Bech
modified: 2018-08-18
---
When using [imap](http://en.wikipedia.org/wiki/Internet_Message_Access_Protocol)
in [mutt](http://en.wikipedia.org/wiki/Mutt_(email_client)) you have the
possibility to use `gpg` to decrypt your password instead of having it as
plaintext in your configuration file (`.muttrc`), see
[ArchWiki](https://wiki.archlinux.org/index.php/Mutt#Passwords_management) how
to do that.

However, if you consider using `POP3`, then you will also need to install and
enable [msmtp](http://msmtp.sourceforge.net) (not strictly needed),
[fetchmail](http://www.fetchmail.info) and
[procmail](http://www.procmail.org). Ubuntu have created a quite nice
[guide](https://help.ubuntu.com/community/MuttAndGmail) of
the steps involved.

Just as `mutt` also `msmtp` have the possibility to use `gpg` in runtime instead
of having the password stored in plaintext. The way to do that in `msmtp` is to
put a line mention `gpg` in your `$HOME/.msmtprc file`.

``` bash
passwordeval    "gpg --quiet --for-your-eyes-only --no-tty --decrypt ~/.msmtp-gmail.gpg"
```

However, `fetchmail` doesn't have the same option. So, `mutt` and `msmtp` is
fine, but you still have to put your password in a cleartext file when
configuring `fetchmail`. Clearly there must be a better way to handle this? I
downloaded the source code
([fetchmail-6.3.26](http://sourceforge.net/projects/fetchmail/files/branch_6.3/fetchmail-6.3.26.tar.xz/download))
and did a quick and dirty hack. I just modified the main function in the file
`fetchmail.c`, so that instead of having to provide the password on command line
(when password is not set in `$HOME/.fetchmailrc`) it makes use of `gpg` similar to how
both mutt and `msmtp` does. It isn't pretty ... but it works (tested on Arch Linux
on a Raspberry PI). To try it out, use the same `gpg` encrypted file as you use
for `msmtp`, i.e, `$HOME/msmtp-gmail.gpg` and patch `fetchmail` using this patch and
rebuild.

# Source
* [fetchmail_gpg.patch](/downloads/patch/fetchmail_gpg.patch)
