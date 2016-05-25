// ┌┐ ┬─┐┌─┐┬ ┬┌─┐┌┬┐┬  ┌─┐ | Bootable Rescue System Tools
// ├┴┐├┬┘└─┐└┬┘└─┐ │ │  └─┐ | @author Luís Ferreira
// └─┘┴└─└─┘ ┴ └─┘ ┴ ┴─┘└─┘ | @license GNU Public License v3

#include <brsystls/cfg/directives.h>

#include <brsystls/video.h>
#include <brsystls/terminal.h>
#include <brsystls/memory.h>
#include <brsystls/cpu.h>

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

void kernel_main() {
	terminal_initialize();
	
	// ...
	terminal_set_color(make_color(COLOR_LIGHT_GREY, COLOR_RED));
	terminal_writeln("                             BRSYSTLS v0.01 - DEBUG                             ");
	terminal_set_color(make_color(COLOR_GREEN, COLOR_BLACK));
	terminal_writeln("Hello, kernel World!");
}