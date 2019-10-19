#include <stdint.h>
#include <string.h>
#include <kernel/idt.h>
#include <kernel/io.h>

idt_entry_t idt_entries[256];
idt_ptr_t idt_ptr;

#define PIC1 0x20
#define PIC2 0xA0

#define ICW1 0x11
#define ICW4 0x01

void init_idt()
{
    idt_ptr.limit = sizeof(idt_entry_t) * 256 -1;
    idt_ptr.base  = (uintptr_t)&idt_entries;

    memset(&idt_entries, 0, sizeof(idt_entry_t)*256);

    idt_set_gate( 0, (uintptr_t)isr0 , 0x08, 0x8E);
    idt_set_gate( 1, (uintptr_t)isr1 , 0x08, 0x8E);
    idt_set_gate( 2, (uintptr_t)isr2 , 0x08, 0x8E);
    idt_set_gate( 3, (uintptr_t)isr3 , 0x08, 0x8E);
    idt_set_gate( 4, (uintptr_t)isr4 , 0x08, 0x8E);
    idt_set_gate( 5, (uintptr_t)isr5 , 0x08, 0x8E);
    idt_set_gate( 6, (uintptr_t)isr6 , 0x08, 0x8E);
    idt_set_gate( 7, (uintptr_t)isr7 , 0x08, 0x8E);
    idt_set_gate( 8, (uintptr_t)isr8 , 0x08, 0x8E);
    idt_set_gate( 9, (uintptr_t)isr9 , 0x08, 0x8E);
    idt_set_gate(10, (uintptr_t)isr10, 0x08, 0x8E);
    idt_set_gate(11, (uintptr_t)isr11, 0x08, 0x8E);
    idt_set_gate(12, (uintptr_t)isr12, 0x08, 0x8E);
    idt_set_gate(13, (uintptr_t)isr13, 0x08, 0x8E);
    idt_set_gate(14, (uintptr_t)isr14, 0x08, 0x8E);
    idt_set_gate(15, (uintptr_t)isr15, 0x08, 0x8E);
    idt_set_gate(16, (uintptr_t)isr16, 0x08, 0x8E);
    idt_set_gate(17, (uintptr_t)isr17, 0x08, 0x8E);
    idt_set_gate(18, (uintptr_t)isr18, 0x08, 0x8E);
    idt_set_gate(19, (uintptr_t)isr19, 0x08, 0x8E);
    idt_set_gate(20, (uintptr_t)isr20, 0x08, 0x8E);
    idt_set_gate(21, (uintptr_t)isr21, 0x08, 0x8E);
    idt_set_gate(22, (uintptr_t)isr22, 0x08, 0x8E);
    idt_set_gate(23, (uintptr_t)isr23, 0x08, 0x8E);
    idt_set_gate(24, (uintptr_t)isr24, 0x08, 0x8E);
    idt_set_gate(25, (uintptr_t)isr25, 0x08, 0x8E);
    idt_set_gate(26, (uintptr_t)isr26, 0x08, 0x8E);
    idt_set_gate(27, (uintptr_t)isr27, 0x08, 0x8E);
    idt_set_gate(28, (uintptr_t)isr28, 0x08, 0x8E);
    idt_set_gate(29, (uintptr_t)isr29, 0x08, 0x8E);
    idt_set_gate(30, (uintptr_t)isr30, 0x08, 0x8E);
    idt_set_gate(31, (uintptr_t)isr31, 0x08, 0x8E);

    // Remap the irq table.

    // send ICW1
    outb(PIC1, ICW1);
    outb(PIC2, ICW1);

    // send ICW2
    outb(PIC1 + 1, 0x20);   
    outb(PIC2 + 1, 0x28);  

    // send ICW3
    outb(PIC1 + 1, 4);   
    outb(PIC2 + 1, 2);

    // send ICW4
    outb(PIC1 + 1, ICW4);
    outb(PIC2 + 1, ICW4);

    outb(PIC1 + 1, 0x0);
    outb(PIC2 + 1, 0x0);

    // disable all IRQs
    // outb(PIC1 + 1, 0xFF);

    idt_set_gate(IRQ0, (uintptr_t)irq0, 0x08, 0x8E);
    idt_set_gate(IRQ1, (uintptr_t)irq1, 0x08, 0x8E);
    idt_set_gate(IRQ2, (uintptr_t)irq2, 0x08, 0x8E);
    idt_set_gate(IRQ3, (uintptr_t)irq3, 0x08, 0x8E);
    idt_set_gate(IRQ4, (uintptr_t)irq4, 0x08, 0x8E);
    idt_set_gate(IRQ5, (uintptr_t)irq5, 0x08, 0x8E);
    idt_set_gate(IRQ6, (uintptr_t)irq6, 0x08, 0x8E);
    idt_set_gate(IRQ7, (uintptr_t)irq7, 0x08, 0x8E);
    idt_set_gate(IRQ8, (uintptr_t)irq8, 0x08, 0x8E);
    idt_set_gate(IRQ9, (uintptr_t)irq9, 0x08, 0x8E);
    idt_set_gate(IRQ10, (uintptr_t)irq10, 0x08, 0x8E);
    idt_set_gate(IRQ11, (uintptr_t)irq11, 0x08, 0x8E);
    idt_set_gate(IRQ12, (uintptr_t)irq12, 0x08, 0x8E);
    idt_set_gate(IRQ13, (uintptr_t)irq13, 0x08, 0x8E);
    idt_set_gate(IRQ14, (uintptr_t)irq14, 0x08, 0x8E);
    idt_set_gate(IRQ15, (uintptr_t)irq15, 0x08, 0x8E);

    idt_flush((uintptr_t)&idt_ptr);
}

void idt_set_gate(uint8_t num, uintptr_t base, uint16_t sel, uint8_t flags)
{
    idt_entries[num].base_low = base & 0xFFFF;
    idt_entries[num].base_high = (base >> 16) & 0xFFFF;

    idt_entries[num].sel     = sel;
    idt_entries[num].always_0 = 0;
    // We must uncomment the OR below when we get to using user-mode.
    // It sets the interrupt gate's privilege level to 3.
    idt_entries[num].access_byte   = flags /* | 0x60 */;
}

void enable_interrupts()
{
    asm volatile("sti");
}

void disable_interrupts()
{
    asm volatile("cli");
}