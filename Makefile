NAME = kernel
ASSEMBLER = i686-elf-as
# ASSEMBLER = nasm
I686_CCC = i686-elf-gcc
I686_CXXC = i686-elf-g++
I686_LINKER = i686-elf-gcc
I386_EMU = qemu-system-i386
DIRMAKER = mkdir

CXXFLAGS = -fno-exceptions -fno-rtti
CFLAGS = -ffreestanding -O2 -Wall -Wextra
# ASMFLAGS = -felf32
LNFLAGS = -ffreestanding -O2 -nostdlib
LGCC = -lgcc

C99 = -std=gnu99

all:
	$(ASSEMBLER) src/boot.S -o bin/obj/boot.o
	$(I686_CCC) -c src/kernel.c -o bin/obj/kernel.o $(C99) $(CFLAGS)
	$(I686_LINKER) -T src/linker.ld -o bin/brsystls.bin $(LNFLAGS) bin/obj/boot.o bin/obj/kernel.o $(LGCC)

debug: 
	$(I386_EMU) -kernel bin/brsystls.bin
