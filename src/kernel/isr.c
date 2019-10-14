#include <stdlib.h>

#include <kernel/io.h>
#include <kernel/isr.h>
#include <kernel/log.h>

static isr_t interrupt_handlers[256] = { NULL };

void isr_handler(registers_t regs)
{
    isr_t handler;
    
    if (regs.int_no > (sizeof(interrupt_handlers) / sizeof(interrupt_handlers[0])))
    {
        error("ISR: %d bigger than interrupt handlers array", regs.int_no);
        return;
    }
    
    handler = interrupt_handlers[regs.int_no];

    if (handler == NULL)
    {
        debug("ISR: %d No handler for event", regs.int_no);
        return;
    }

    handler(&regs);
}

void irq_handler(registers_t regs)
{
    isr_t handler;

    if (regs.int_no >= 40)
    { 
        outb(0xA0, 0x20); 
    }

    outb(0x20, 0x20);

    if (regs.int_no > (sizeof(interrupt_handlers) / sizeof(interrupt_handlers[0])))
    {
        error("IRQ: %d bigger than possible handler", regs.int_no);
        return;
    }

    handler = interrupt_handlers[regs.int_no];

    if (handler == NULL)
    {
        debug("IRQ: %d No handler for event", regs.int_no);
        return;
    }
    
    handler(&regs);
}

void register_interrupt_handler(uint16_t n, isr_t handler)
{
    if (handler == NULL)
        panic("Attempting to register NULL handler");

    if (n >= (sizeof(interrupt_handlers) / sizeof(interrupt_handlers[0])))
        panic("Attempting to register handler bigger than array");

    log("Registering handler %d", n);

    interrupt_handlers[n] = handler;
}