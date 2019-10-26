#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <kernel/kernel.h>
#include <kernel/keyboard.h>
#include <kernel/timer.h>
#include <kernel/framebuffer.h>
#include <kernel/log.h>
#include <kernel/gdt.h>
#include <kernel/idt.h>
#include <kernel/paging.h>
#include <kernel/multiboot2.h>

void kernel_main(multiboot_info_t* mbi) {
	// The IDT and GDT tables need to be initialized. The CPU uses these tables
    // to direct interrupts to the kernel and to describe the memory layout
    // of the kernel.
	init_gdt();
	init_idt();

	// Initializes the Framebuffer, this will allow text rendering on the screen
    // This also does not use any systems other than IO ports.
	init_framebuffer(mbi);
	debug("Kernel start: 0x%x", &_KERNEL_START);
    debug("Kernel end: 0x%x", &_KERNEL_END);
	log("Booting...");

	// The first module to initialize is the Page Allocator. This will provide
    // virtual memory with paging. Paging IS ACTIVATED once init_page_allocator
    // is called. We must now remember to allocate the page of memory we touch
    // or the kernel will panic. This is good to enable it first because we
    // will detect memory problems earlier in the development.
    init_paging();
    log("Paging setup.");

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


// TEST SCENARIOS ===========================================================

// #define TEST_PAGE_FAULT 1

#ifdef TEST_PAGE_FAULT
	uintptr_t *ptr = (uintptr_t*)0xA0000000;
   	uintptr_t do_page_fault = *ptr;
	warn("%d", do_page_fault);
#endif

// END TEST SCENARIOS =======================================================

	while (1)
	{
		cpu_idle();
	}
}