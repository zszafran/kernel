#include <stdio.h>
#include <stdint.h>

#include <kernel/keyboard.h>
#include <kernel/timer.h>
#include <kernel/framebuffer.h>
#include <kernel/log.h>
#include <kernel/gdt.h>
#include <kernel/idt.h>
#include <kernel/multiboot2.h>

// TODO: Read these values ondemand instead of parsing. 
multiboot_info_t mbi;

void kernel_main(uintptr_t mbi_ptr) {
	// Parse the information passed in from multiboot.
	read_multiboot(mbi_ptr, &mbi);

	// The IDT and GDT tables need to be initialized. The CPU uses these tables
    // to direct interrupts to the kernel and to describe the memory layout
    // of the kernel.
	init_gdt();
	init_idt();

	// Initializes the Framebuffer, this will allow text rendering on the screen
    // This also does not use any systems other than IO ports.
	init_framebuffer(
		mbi.framebuffer_tag->common.framebuffer_addr,
      	mbi.framebuffer_tag->common.framebuffer_width,
      	mbi.framebuffer_tag->common.framebuffer_height);
	clear_framebuffer();
	log("Booting...");

	// Print the multiboot into payload.
	print_multiboot(&mbi);

	// Register the interrupt handler for the timer chip. This will get us
    // a steady call every MS. The timer DOES NOT start ticking at this time.
    // Only when the interrupts are enabled will we receive the calls.
    // This sends an update to the kernel scheduler to update the running
    // task status.
	init_timer(TIMER_FREQ_1MS);
	log("Timer setup for 1ms ticks.");

	// Register the interrupt handler for the keyboard.
	init_keyboard();
	log("Keyboard setup.");

	// Globally enable the interrupts. This will start popping up the timer
    // and the scheduler will start switching to other threads periodically.
	enable_interrupts();
	log("Interrupts enabled.");

	debug("Hello, kernel World!");

	while (1)
	{
		cpu_idle();
	}
}