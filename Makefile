NAME = kernel
ASSEMBLER = nasm
CCC = i686-elf-gcc
CXXC = i686-elf-g++
LINKER = i686-elf-gcc
EMU = qemu-system-i386

CXXFLAGS = -fno-exceptions -fno-rtti
CFLAGS = -ffreestanding -O2 -Wall -Wextra
ASMFLAGS = -felf32

C99 = -std=gnu99
