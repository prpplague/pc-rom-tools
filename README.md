# PC ROM Tools

Basic tools for creating BIOS Extension ROMs for the IBM PCjr and IBM PC/XT/AT

Originally Created by Shaos and Licenced under GPLv3

PCjr Testing

generate an executable com file:

nasm pcjr_test.asm -fbin -o test.com

generate a binary rom image:

pcjrcart test.com

the resulting test.bin file can be flash to your EEPROM


Dosbox Testing:

generate an executable com file:"

nasm dosbox_test.asm -fbin -i test.com

execute dosbox:

dosbox -machine cga test.com

