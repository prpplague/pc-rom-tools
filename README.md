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
$ nasm pcjr_test.asm -fbin -o test.com
</pre>
generate a binary rom image:
<pre>
$ pcjrcart test.com
</pre>

the resulting test.bin file can be flash to your EEPROM. 

This image can also be generated with make:
<pre>
$ make pcjr
nasm pcjr_test.asm -fbin -o test.com
./pcjrcart test.com
test.com 52
ROM size is 512 bytes (1)
Calculated CRC is 0x714A
Corrected CRC is 0x0000
</pre>


Dosbox Testing:

to generate an executable com file:"
<pre>
$ nasm dosbox_test.asm -fbin -i test.com
</pre>

This image can also be generated with make:
<pre>
$ make dosbox
nasm dosbox_test.asm -fbin -o test.com
</pre>

execute dosbox:

<pre>
$ dosbox -machine cga test.com
</pre>


Generic ROM Testing:

To generate an executable com file:

<pre>
$ nasm generic_test.asm -fbin -o test.com
</pre>

generate a binary rom image:

<pre>
$ genrom test.com
</pre>

the resulting test.bin file can be flash to your EEPROM.

This image can also be generated with make:

<pre>
$ make generic
nasm generic_test.asm -fbin -o test.com
./genrom test.com
test.com 52
ROM size is 512 bytes (1)
8-bit Checksum=27

</pre>


