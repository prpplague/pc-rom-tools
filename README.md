# PC ROM Tools

Basic tools for creating BIOS Extension ROMs for the IBM PCjr and IBM PC/XT/AT

Originally Created by Shaos and Licenced under GPLv3

To build tools simply issue the make command.

$ make
gcc -o pcjrcart pcjrcart.c crc16.c
gcc -o genrom genrom.c


PCjr Testing

to generate an executable com file:

nasm pcjr_test.asm -fbin -o test.com

generate a binary rom image:

pcjrcart test.com

the resulting test.bin file can be flash to your EEPROM. This image can also
be generated with make:

make pcjr



Dosbox Testing:

to generate an executable com file:"

nasm dosbox_test.asm -fbin -i test.com

This image can also be generated with make:

make dosbox

execute dosbox:

dosbox -machine cga test.com


Generic ROM Testing:

to generate an executable com file:

nasm generic_test.asm -fbin -o test.com

generate a binary rom image:

genrom test.com

the resulting test.bin file can be flash to your EEPROM. This image can also
be generated with make:

make generic


