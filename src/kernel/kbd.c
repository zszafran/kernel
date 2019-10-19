#include <stdint.h>
#include <boot/idt.h>
#include <kernel/io.h>
#include <kernel/isr.h>
#include <kernel/log.h>
#include <kernel/kbd.h>

#define KEY_DEVICE    0x60
#define KEY_PENDING   0x64

static void keyboard_handler(__attribute__((unused)) struct registers *regs)
{
    uint16_t scancode;
    while(inb(KEY_PENDING) & 2);
    scancode = inb(KEY_DEVICE);
    log("Keyboard press: %d", scancode);
}

void init_kbd(void)
{ 
    register_interrupt_handler(IRQ1, &keyboard_handler);
}