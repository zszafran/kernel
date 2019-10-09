#include <stdio.h>
#include <stdint.h>

#include <kernel/tty.h>

extern const uint32_t multiboot_ptr;
extern const uint32_t multiboot_magic;

void kernel_main(void) {
	terminal_initialize();
	printf("Hello, kernel World!\n");
}