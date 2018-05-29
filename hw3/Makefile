CC = gcc
CFLAGS = -Wall -fno-stack-protector -g
ASM = nasm
ASMFLAGS = -f elf64

.PHONY: test%

test%: test%.o start.o libminic.o libminic.so
	$(CC) -nostdlib -g -o  $@ $< start.o libminic.o
	$(CC) -nostdlib -g -no-pie -o  $@s $< start.o libminic.so

%.o: %.c
	$(CC) $(CFLAGS) -c $<

%.o: %.asm
	$(ASM) $(ASMFLAGS) $< -o $@

libminic.so: libminic.o
	ld -shared -o libminic.so libminic.o

