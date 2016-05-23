# ┌┐ ┬─┐┌─┐┬ ┬┌─┐┌┬┐┬  ┌─┐ | Bootable Rescue System Tools
# ├┴┐├┬┘└─┐└┬┘└─┐ │ │  └─┐ | @author Luís Ferreira
# └─┘┴└─└─┘ ┴ └─┘ ┴ ┴─┘└─┘ | @license GNU Public License v3

NAME = kernel
ASSEMBLER = i686-elf-as
# ASSEMBLER = nasm
I686_CCC = ./.ccompiler/bin/i686-elf-gcc
I686_CXXC = ./.ccompiler/bin/i686-elf-g++
I686_LINKER = ./.ccompiler/bin/i686-elf-gcc
I386_EMU = qemu-system-i386
DIRMAKER = mkdir
GRUB = grub-mkrescue
MKDIR = mkdir -p
RM = rm -rf
CP = cp

CXXFLAGS = -fno-exceptions -fno-rtti
CFLAGS = -ffreestanding -O2 -Wall -Wextra -I/usr/include/ -Isrc/headers/
# ASMFLAGS = -felf32
LNFLAGS = -ffreestanding -O2 -nostdlib
GRBFLAGS = -d /usr/lib/grub/i386-pc/
LGCC = -lgcc

C99 = -std=gnu99

all: compile mk_iso run

debug: compile run_debug

compile: mk_dir c_main c_video c_terminal asm_boot mk_bin

mk_dir:
	$(MKDIR) bin/obj/
	$(MKDIR) bin/obj/video
	$(MKDIR) bin/obj/terminal

asm_boot:
	$(ASSEMBLER) src/boot.S -o bin/obj/boot.o

c_main:
	$(I686_CCC) -c src/kernel.c -o bin/obj/kernel.o $(C99) $(CFLAGS)

c_video:
	$(I686_CCC) -c src/video/colors.c -o bin/obj/video/colors.o $(C99) $(CFLAGS)
	$(I686_CCC) -c src/video/detect.c -o bin/obj/video/detect.o $(C99) $(CFLAGS)

c_terminal:
	$(I686_CCC) -c src/terminal/cursor.c -o bin/obj/terminal/cursor.o $(C99) $(CFLAGS)

mk_bin:
	$(I686_LINKER) -T src/linker.ld -o bin/brsystls.bin $(LNFLAGS) \
	bin/obj/boot.o \
	bin/obj/kernel.o \
	bin/obj/video/colors.o \
	bin/obj/video/detect.o \
	bin/obj/terminal/cursor.o \
	$(LGCC)

mk_iso:
	$(MKDIR) .temp/boot/grub/
	$(CP) bin/brsystls.bin .temp/boot/brsystls.bin
	$(CP) src/grub/grub.cfg .temp/boot/grub/grub.cfg
	$(GRUB) $(GRBFLAGS) -o bin/brsystls.iso .temp
	$(RM) .temp

run_debug: 
	$(I386_EMU) -kernel bin/brsystls.bin

run:
	$(I386_EMU) -cdrom bin/brsystls.iso