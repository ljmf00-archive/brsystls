// ┌┐ ┬─┐┌─┐┬ ┬┌─┐┌┬┐┬  ┌─┐ | Bootable Rescue System Tools
// ├┴┐├┬┘└─┐└┬┘└─┐ │ │  └─┐ | @author Luís Ferreira
// └─┘┴└─└─┘ ┴ └─┘ ┴ ┴─┘└─┘ | @license GNU Public License v3

#include <asm/io.h>
#include <stddef.h>
#include <stdint.h>

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t * terminal_buffer;

void terminal_update_cursor(int row, int col);
void terminal_set_color(uint8_t color);
void terminal_write_char(char c);
void terminal_write_string(const char* data);
void terminal_writeln(const char* data);
void terminal_write_nl(void);
void terminal_clear(void);
void terminal_initialize();