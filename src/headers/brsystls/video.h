// ┌┐ ┬─┐┌─┐┬ ┬┌─┐┌┬┐┬  ┌─┐ | Bootable Rescue System Tools
// ├┴┐├┬┘└─┐└┬┘└─┐ │ │  └─┐ | @author Luís Ferreira
// └─┘┴└─└─┘ ┴ └─┘ ┴ ┴─┘└─┘ | @license GNU Public License v3

#include <stdint.h>

extern enum video_type;
extern uint16_t detect_bios_area_hardware(void);
extern enum video_type get_bios_area_video_type(void);