---
layout: post
title: Perl pack and unpack
date: 2012-03-04 00:15:48
comments: true
category: Coding
authors:Joakim Bech
modified: 2018-08-18
---
<img alt="Perl logo" src="{filename}/images/perlpap/logo_perl.jpg" align="right">
When you have to read and write binary data using Perl, then you preferably use
the built in functions pack and unpack. With the pack function you will create
a string which will be different depending on what kind of template you provide
to the pack function (the unpack does the same, but in the opposite direction).

I was writing a simple Perl script that was reading a binary file which
contained data that originated from a c `struct`. I.e., I wanted to parse the
binary file and print what the values would be if the binary file was read into
the c struct.

Let's say that the struct is on the format:

```c
struct binary_data {
    uint32_t a;
    uint32_t b;
    uint8_t c;
}
```

I.e, we have data consisting of 4 bytes of `a`, 4 bytes of `b` and 1 byte of
`c`. Let us say that the binary files consist of the following values
```
a = 196 dec (0xC4 hex)
b = 4293844428 dec (0xFFEEDDCC hex)
c = 75 dec (0x4B hex)
```

then our binary file, `binary_data.bin` would contain this:
```
c4 00 00 00 cc dd ee ff 4b
```

To be able to read this back and print the values in decimal or hex, you simply
start by reading the size of each element in the struct one by one and for each
item you unpack the data according to the size of the element in the struct.
For `uint32_t` you use `L` and for `uint8_t` `C`. A complete listing of the
different templates (as they are called in Perl) could be found in the Perl
documentation. Be careful about little- vs big-endian when you select template.

Below is a Perl script that creates the binary file, then read the data back
from the file and print the values both in decimal and hex.

```perl
#!/usr/bin/perl
use strict;
use warnings;

binmode FILE;
my $buf;

# Write decimal values as binary data.
open FILE, ">binary_data.bin" or die $!;

my $data = pack 'L', 196;
print FILE $data;

$data = pack 'L', 4293844428;
print FILE $data;

$data = pack 'C', 75;
print FILE $data;

close FILE;

# Read back binary data to decimal value.
open FILE, "binary_data.bin" or die $!;

read FILE, $buf, 4;
$data = unpack 'L', $buf;
print $data . " - " . sprintf("%x", $data) . "\n";

read FILE, $buf, 4;
$data = unpack 'L', $buf;
print $data . " - " . sprintf("%x", $data) . "\n";

read FILE, $buf, 1;
$data = unpack 'C', $buf;
print $data . " - " . sprintf("%x", $data) . "\n";

close FILE;
```
