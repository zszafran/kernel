#pragma once

#include <stdint.h>

struct idt_entry_struct
{
	uint16_t base_low;
	uint16_t sel;
	uint8_t always_0;
	uint8_t access_byte;
	uint16_t base_high;
}__attribute__((packed));
typedef struct idt_entry_struct idt_entry_t;

struct idt_ptr_struct
{
	uint16_t limit;
	uintptr_t base;
}__attribute__((packed));
typedef struct idt_ptr_struct idt_ptr_t;

enum IRQS {
    IRQ0    = 32,
    IRQ1    = 33,
    IRQ2    = 34,
    IRQ3    = 35,
    IRQ4    = 36,
    IRQ5    = 37,
    IRQ6    = 38,
    IRQ7    = 39,
    IRQ8    = 40,
    IRQ9    = 41,
    IRQ10   = 42,
    IRQ11   = 43,
    IRQ12   = 44,
    IRQ13   = 45,
    IRQ14   = 46,
    IRQ15   = 47,
};

void init_idt();
void idt_set_gate(uint8_t, uintptr_t, uint16_t, uint8_t);
void enable_interrupts();
void disable_interrupts();

extern void idt_flush(uintptr_t);

extern void isr0 ();
extern void isr1 ();
extern void isr2 ();
extern void isr3 ();
extern void isr4 ();
extern void isr5 ();
extern void isr6 ();
extern void isr7 ();
extern void isr8 ();
extern void isr9 ();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();

extern void irq0(void);
extern void irq1(void);
extern void irq2(void);
extern void irq3(void);
extern void irq4(void);
extern void irq5(void);
extern void irq6(void);
extern void irq7(void);
extern void irq8(void);
extern void irq9(void);
extern void irq10(void);
extern void irq11(void);
extern void irq12(void);
extern void irq13(void);
extern void irq14(void);
extern void irq15(void);