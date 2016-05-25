// ┌┐ ┬─┐┌─┐┬ ┬┌─┐┌┬┐┬  ┌─┐ | Bootable Rescue System Tools
// ├┴┐├┬┘└─┐└┬┘└─┐ │ │  └─┐ | @author Luís Ferreira
// └─┘┴└─└─┘ ┴ └─┘ ┴ ┴─┘└─┘ | @license GNU Public License v3

#include <brsystls/memory.h>
#include <brsystls/serial.h>
#include <asm/io.h>

__asm__(".code16gcc\n");

int __attribute__((noinline)) __attribute__((regparm(3))) memory_bios_detect(SMAP_entry_t* buffer, int maxentries)
{
	uint32_t contID = 0;
	int entries = 0, signature, bytes;
	do 
	{
		__asm__ __volatile__ ("int  $0x15" 
				: "=a"(signature), "=c"(bytes), "=b"(contID)
				: "a"(0xE820), "b"(contID), "c"(24), "d"(0x534D4150), "D"(buffer));
		if (signature != 0x534D4150) 
			return -1;
		if (!(bytes > 20 && (buffer->ACPI & 0x0001) == 0))
		{
			buffer++;
			entries++;
		}
	} 
	while (contID != 0 && entries < maxentries);
	return entries;
}

int memory_detect(void) {
    SMAP_entry_t* smap = (SMAP_entry_t*) 0x1000;
    const int smap_size = 0x2000;
    int entry_count = memory_bios_detect(smap, smap_size / sizeof(SMAP_entry_t));
    if(entry_count == -1)
    {
        return 0;
    }
    else
    {
        return entry_count;
    }
}

unsigned short memory_cmos_get_total(void)
{
    unsigned char lowmem, highmem;
    serial_write(0x70, 0x30);
    lowmem = serial_read(0x71);
    serial_write(0x70, 0x31);
    highmem = serial_read(0x71);
    return lowmem | highmem << 8;
}

