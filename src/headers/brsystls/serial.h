// ┌┐ ┬─┐┌─┐┬ ┬┌─┐┌┬┐┬  ┌─┐ | Bootable Rescue System Tools
// ├┴┐├┬┘└─┐└┬┘└─┐ │ │  └─┐ | @author Luís Ferreira
// └─┘┴└─└─┘ ┴ └─┘ ┴ ┴─┘└─┘ | @license GNU Public License v3

#include <asm/io.h>
#include <stdint.h>

void serial_initialize(uint16_t port);
int serial_received(uint16_t serial_port);
char serial_read(uint16_t serial_port);
int serial_is_transmit_empty(uint16_t serial_port);
void serial_write(uint16_t serial_port, uint8_t a);