// ┌┐ ┬─┐┌─┐┬ ┬┌─┐┌┬┐┬  ┌─┐ | Bootable Rescue System Tools
// ├┴┐├┬┘└─┐└┬┘└─┐ │ │  └─┐ | @author Luís Ferreira
// └─┘┴└─└─┘ ┴ └─┘ ┴ ┴─┘└─┘ | @license GNU Public License v3

#include <brsystls/terminal.h>
#include <brsystls/video.h>
#include <stringdef.h>

void terminal_write_char(char c) {
	terminal_put_entry_at(c, terminal_color, terminal_column, terminal_row);
	if (++terminal_column == VGA_WIDTH) {
		terminal_column = 0;
		if (++terminal_row == VGA_HEIGHT) {
			terminal_row = 0;
		}
	}
}

void terminal_write_string(const char* data) {
	size_t datalen = strlen(data);
	for (size_t i = 0; i < datalen; i++)
		terminal_write_char(data[i]);
}

void terminal_writeln(const char* data) {
    terminal_write_string(data);
    if(terminal_column != 0) terminal_row++;
    terminal_column = 0;
}