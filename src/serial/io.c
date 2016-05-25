// ┌┐ ┬─┐┌─┐┬ ┬┌─┐┌┬┐┬  ┌─┐ | Bootable Rescue System Tools
// ├┴┐├┬┘└─┐└┬┘└─┐ │ │  └─┐ | @author Luís Ferreira
// └─┘┴└─└─┘ ┴ └─┘ ┴ ┴─┘└─┘ | @license GNU Public License v3

#include <brsystls/serial.h>

void serial_initialize(uint16_t port) {
   outb(port + 1, 0x00);
   outb(port + 3, 0x80);
   outb(port + 0, 0x03);
   outb(port + 1, 0x00);
   outb(port + 3, 0x03);
   outb(port + 2, 0xC7);
   outb(port + 4, 0x0B);
}

int serial_received(uint16_t serial_port) {
   return inb(serial_port + 5) & 1;
}

char serial_read(uint16_t serial_port) {
   while (serial_received(serial_port) == 0);
 
   return inb(serial_port);
}

int serial_is_transmit_empty(uint16_t serial_port) {
   return inb(serial_port + 5) & 0x20;
}

void serial_write(uint16_t serial_port, uint8_t a) {
   while (serial_is_transmit_empty(serial_port) == 0);
   outb(serial_port,a);
}