NAME = kernel
ASSEMBLER = nasm
CCC = i686-elf-gcc
CXXC = i686-elf-g++
LINKER = i686-elf-gcc
EMU = qemu-system-i386
DIRMAKER = mkdir

CXXFLAGS = -fno-exceptions -fno-rtti
CFLAGS = -ffreestanding -O2 -Wall -Wextra
ASMFLAGS = -felf32
LNFLAGS = -ffreestanding -O2 -nostdlib
LGCC = -lgcc

C99 = -std=gnu99

all:
	$(ASSEMBLER) $(ASMFLAGS) src/boot.asm -o bin/obj/boot.o
	$(CCC) -c src/kernel.c -o bin/obj/kernel.o $(C99) $(CFLAGS)
	$(LINKER) -T src/linker.ld -o bin/brsystls.bin $(LNFLAGS) bin/obj/boot.o bin/obj/kernel.o $(LGCC)

debug: 
	$(EMU) -kernel bin/brsystls.bin
