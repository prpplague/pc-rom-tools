# PC ROM Tools

Basic tools for creating BIOS Extension ROMs for the IBM PCjr and IBM PC/XT/AT

Originally Created by Shaos and Licenced under GPLv3

To build tools simply issue the make command.

<pre>
$ make
gcc -o pcjrcart pcjrcart.c crc16.c
gcc -o genrom genrom.c
</pre>

PCjr Testing

to generate an executable com file:
<pre>
nasm pcjr_test.asm -fbin -o test.com
</pre>
generate a binary rom image:
<pre>
pcjrcart test.com
</pre>

the resulting test.bin file can be flash to your EEPROM. This image can also
be generated with make:
<pre>
make pcjr
</pre>


Dosbox Testing:

to generate an executable com file:"
<pre>
nasm dosbox_test.asm -fbin -i test.com
</pre>

This image can also be generated with make:

<pre>
make dosbox
</pre>
execute dosbox:

<pre>
dosbox -machine cga test.com
</pre>


Generic ROM Testing:

to generate an executable com file:

<pre>
nasm generic_test.asm -fbin -o test.com
</pre>

generate a binary rom image:

<pre>
genrom test.com
</pre>

the resulting test.bin file can be flash to your EEPROM. This image can also
be generated with make:

<pre>
make generic
</pre>


