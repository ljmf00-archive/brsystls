// ┌┐ ┬─┐┌─┐┬ ┬┌─┐┌┬┐┬  ┌─┐ | Bootable Rescue System Tools
// ├┴┐├┬┘└─┐└┬┘└─┐ │ │  └─┐ | @author Luís Ferreira
// └─┘┴└─└─┘ ┴ └─┘ ┴ ┴─┘└─┘ | @license GNU Public License v3

#include <stdint.h>

typedef struct SMAP_entry {
 
	uint32_t BaseL;
	uint32_t BaseH;
	uint32_t LengthL;
	uint32_t LengthH;
	uint32_t Type;
	uint32_t ACPI;
 
}__attribute__((packed)) SMAP_entry_t;

int memory_detect(void);
int __attribute__((noinline)) __attribute__((regparm(3))) memory_bios_detect(SMAP_entry_t* buffer, int maxentries);
unsigned short memory_cmos_get_total(void);