---
layout: post
title: Using libcurl with minimal dependencies
date: 2010-08-05 00:13:15
comments: true
category: Coding
authors:Joakim Bech
modified: 2018-08-18
---
<img alt="LibCURL logo" src="{filename}/images/libcurldep/logo_curl-200x150.jpg" align="right">
For an ongoing project I needed to retrieve webpages from my C-program and
first I used sockets directly, but then I thought why not try use libcurl? If I
could use libcurl and link it statically then I would get the good features
from libcurl, but still could make my application stand alone.

With my current setup running Debian (Lenny), I tried to just apt-get the libraries
(`libcurl4-openssl-dev`) and build using those libraries That went fine until I
tried to link them statically with my application. After reading different mail
archives, forum and tried on my own I got my application to link (static) with
libcurl. Basically what I needed to do was.

* Download libcurl source
* Compile libcurl myself (disable one define, more about that below).
* Point to my own built libcurl.a library when building my own application.

So to save some headache for myself next time I want to do it or for someone
else reading this I've listed the steps I had to do to get this to work.

# Download libcurl source
As of writing this, the latest version of libcurl was 7.21.0 so I downloaded
and unpacked the source.

```bash
wget http://curl.haxx.se/download/curl-7.21.0.tar.bz2
tar xjvf curl-7.21.0.tar.bz2
{% endcodeblock %}
```

# Compile libcurl
Next it was time to run `./configure` and `make`. Here I basically disabled
everything for libcurl except `HTTP` and `FILE`.

```bash
./configure --prefix=$HOME/devel/libcurl --disable-dict --disable-ftp --disable-imap --disable-ldap --disable-ldaps --disable-pop3 --disable-proxy --disable-rtsp --disable-shared --disable-smtp --disable-telnet --disable-tftp --disable-zlib --without-ca-bundle --without-gnutls --without-libidn --without-librtmp --without-libssh2 --without-nss --without-ssl --without-zlib
```

Edit the file `lib/curl_config.h` which is generated during the configure step.
In this file we uncomment the line saying

```bash
/* Define to 1 if you have the clock_gettime function and monotonic timer. */
//#define HAVE_CLOCK_GETTIME_MONOTONIC 1
```

If I didn't do this, then I would have a dependency to `librt` which I didn't want to.

```bash
make
make install
```

Now I was done with libcurl, next I should use this library in my application.

# Build the application using libcurl

To make things simple when describing this I instead use the file
[simple.c](http://curl.haxx.se/libcurl/c/simple.html)
which is found on [libcurl's](http://curl.haxx.se/libcurl) site.

In [simple_libcurl.tar.gz](/downloads/libcurldep/simple_libcurl.tar.gz) I've
put together the source and a Makefile which builds using the library just
created. The magic is the `LDFLAGS` line used in the linking step on line 12
and 24 below. I.e. on line 12 I had have to point the folder where the
library is located that I had built myself (`-L/path/to/my/libcurl.a`) and I
still needed to tell the linker that I wanted to use libcurl, hence the
`-lcurl` parameter.

```Makefile
SRCDIR 	:= src
OBJDIR	:= obj
SRC		:= $(patsubst $(SRCDIR)/%.c, %.c, $(wildcard $(SRCDIR)/*.c))
OBJS	:= $(addprefix $(OBJDIR)/, $(patsubst %.c, %.o, $(SRC)))

INCDIR	:= inc

CC		:= gcc
CFLAGS	+= $(addprefix -I, $(INCDIR))
CFLAGS	+= -I/home/jyx/devel/libcurl/include

LDFLAGS	:= -L/home/jyx/devel/libcurl/lib -lcurl

.PHONY : all clean

all: main

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@echo " (CC)	$<"
	@$(CC) $(CFLAGS) -c $< -o $@

main: $(OBJS)
	@echo "Create binary: $@"
	@$(CC) -o main $+ $(LDFLAGS)

clean:
	rm -f $(OBJDIR)/* main
```

When this is achieved, then you have a quite clean binary when it comes to
dependencies. In the example code in `simple_libcurl` I now have these
dependencies on a machine running Debian (Lenny).

```bash
$ ldd main
    linux-vdso.so.1 =>  (0x00007f157db66000)
    libc.so.6 => /lib/libc.so.6 (0x00007f157d5f9000)
    /lib64/ld-linux-x86-64.so.2 (0x00007f157d94c000)
```

Have fun with libcurl!
