#include <stdio.h>
#include <stdint.h>

#include <kernel/tty.h>
#include <kernel/log.h>

extern const uint32_t multiboot_ptr;
extern const uint32_t multiboot_magic;

void kernel_main(void) {
	terminal_initialize();
	log("Booting...");
	debug("Hello, kernel World!");
}