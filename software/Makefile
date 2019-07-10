default: pcjrcart.c crc16.c
	gcc -o pcjrcart pcjrcart.c crc16.c
	gcc -o genrom genrom.c

clean:
	rm -rf pcjrcart genrom *.bin *.com

dosbox:
	nasm dosbox_test.asm -fbin -o test.com
	./genrom test.com

pcjr:
	nasm pcjr_test.asm -fbin -o test.com
	./pcjrcart test.com

generic:
	nasm generic_test.asm -fbin -o test.com
	./genrom test.com


