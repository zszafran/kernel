#include <stdint.h>

#include <kernel/idt.h>
#include <kernel/interrupts.h>
#include <kernel/io.h>
#include <kernel/timer.h>
#include <kernel/log.h>

#define PIT_A       0x40
#define PIT_B       0x41
#define PIT_C       0x42
#define PIT_CONTROL 0x43
#define PIT_SET     0x36
#define PIT_MASK    0xFF
#define PIT_SCALE   1193180

static uint32_t tick = 0;

static void timer_callback(__attribute__((unused)) struct registers *regs)
{
    ++tick;

    if (tick % 6000 == 0)
        debug("Timer Tick: %d", tick);
}

void init_timer(uint32_t frequency)
{
    int32_t divisor;

    register_interrupt_handler(IRQ0, &timer_callback);

    divisor = PIT_SCALE / frequency;
    
    outb(PIT_CONTROL, PIT_SET);
    outb(PIT_A, divisor & PIT_MASK);
    outb(PIT_A, (divisor >> 8) & PIT_MASK);
}