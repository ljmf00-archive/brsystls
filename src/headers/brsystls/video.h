// ┌┐ ┬─┐┌─┐┬ ┬┌─┐┌┬┐┬  ┌─┐ | Bootable Rescue System Tools
// ├┴┐├┬┘└─┐└┬┘└─┐ │ │  └─┐ | @author Luís Ferreira
// └─┘┴└─└─┘ ┴ └─┘ ┴ ┴─┘└─┘ | @license GNU Public License v3

#include <stddef.h>
#include <stdint.h>

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;

enum vga_color {
	COLOR_BLACK = 0x0,
	COLOR_BLUE = 0x1,
	COLOR_GREEN = 0x2,
	COLOR_CYAN = 0x3,
	COLOR_RED = 0x4,
	COLOR_MAGENTA = 0x5,
	COLOR_YELLOW = 0x6,
	COLOR_LIGHT_GREY = 0x7,
	COLOR_DARK_GREY = 0x8,
	COLOR_LIGHT_BLUE = 0x9,
	COLOR_LIGHT_GREEN = 0xA,
	COLOR_LIGHT_CYAN = 0xB,
	COLOR_LIGHT_RED = 0xC,
	COLOR_LIGHT_MAGENTA = 0xD,
	COLOR_LIGHT_YELLOW = 0xE,
	COLOR_WHITE = 0xF,
};

enum video_type
{
    VIDEO_TYPE_NONE = 0x00,
    VIDEO_TYPE_COLOUR = 0x20,
    VIDEO_TYPE_MONOCHROME = 0x30,
};

uint16_t detect_bios_area_hardware(void);
enum video_type get_bios_area_video_type(void);
uint16_t make_vga_entry(char c, uint8_t color);
uint8_t make_color(enum vga_color fg, enum vga_color bg);