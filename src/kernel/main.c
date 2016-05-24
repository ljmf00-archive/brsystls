// ┌┐ ┬─┐┌─┐┬ ┬┌─┐┌┬┐┬  ┌─┐ | Bootable Rescue System Tools
// ├┴┐├┬┘└─┐└┬┘└─┐ │ │  └─┐ | @author Luís Ferreira
// └─┘┴└─└─┘ ┴ └─┘ ┴ ┴─┘└─┘ | @license GNU Public License v3

#include <brsystls/cfg/directives.h>

#include <brsystls/video.h>
#include <brsystls/terminal.h>

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
	terminal_writeln("Hello, kernel World!");
	// Tell APIC timer to use divider 16
        write(APIC_REGISTER_TIMER_DIV, 0x3);
 
        // Prepare the PIT to sleep for 10ms (10000µs)
        pit_prepare_sleep(10000);
 
        // Set APIC init counter to -1
        write(APIC_REGISTER_TIMER_INITCNT, 0xFFFFFFFF);
 
        // Perform PIT-supported sleep
        pit_perform_sleep();
 
        // Stop the APIC timer
        write(APIC_REGISTER_LVT_TIMER, APIC_LVT_INT_MASKED);
 
        // Now we know how often the APIC timer has ticked in 10ms
        uint32_t ticksIn10ms = 0xFFFFFFFF - read(APIC_REGISTER_TIMER_CURRCNT);
 
        // Start timer as periodic on IRQ 0, divider 16, with the number of ticks we counted
        write(APIC_REGISTER_LVT_TIMER, 32 | APIC_LVT_TIMER_MODE_PERIODIC);
        write(APIC_REGISTER_TIMER_DIV, 0x3);
        write(APIC_REGISTER_TIMER_INITCNT, ticksIn10ms);
}