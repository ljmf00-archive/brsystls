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

compile: mk_dir c_main c_video c_terminal c_lib asm_boot mk_bin

mk_dir:
	$(MKDIR) bin/obj/kernel
	$(MKDIR) bin/obj/video
	$(MKDIR) bin/obj/terminal
	$(MKDIR) bin/obj/lib/

asm_boot:
	$(ASSEMBLER) src/kernel/boot.S -o bin/obj/kernel/boot.o

c_main:
	$(I686_CCC) -c src/kernel/main.c -o bin/obj/kernel/main.o $(C99) $(CFLAGS)

c_video:
	$(I686_CCC) -c src/video/color.c -o bin/obj/video/color.o $(C99) $(CFLAGS)

c_terminal:
	$(I686_CCC) -c src/terminal/cursor.c -o bin/obj/terminal/cursor.o $(C99) $(CFLAGS)
	$(I686_CCC) -c src/terminal/write.c -o bin/obj/terminal/write.o $(C99) $(CFLAGS)
	$(I686_CCC) -c src/terminal/terminal.c -o bin/obj/terminal.o $(C99) $(CFLAGS)

c_lib:
	$(I686_CCC) -c src/lib/stringdef.c -o bin/obj/lib/stringdef.o $(C99) $(CFLAGS)

mk_bin:
	$(I686_LINKER) -T src/kernel/linker.ld -o bin/brsystls.bin $(LNFLAGS) \
	bin/obj/kernel/boot.o \
	bin/obj/kernel/main.o \
	bin/obj/video/color.o \
	bin/obj/terminal/cursor.o \
	bin/obj/terminal.o \
	bin/obj/terminal/write.o \
	bin/obj/lib/stringdef.o \
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