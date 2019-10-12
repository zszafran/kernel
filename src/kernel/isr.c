#include <kernel/isr.h>
#include <kernel/log.h>

void isr_handler(registers_t regs)
{
    if (regs.int_no != 0xd)
        debug("ISR recieved: 0x%x", regs.int_no);
}

void irq_handler(registers_t regs)
{
    debug("IRQ recieved: 0x%x", regs.int_no);
    // if (regs.int_no >= 40) 
    //     outb(0xA0, 0x20); // Send reset signal to slave
    
    // // Send reset signal to master
    // outb(0x20, 0x20);
}