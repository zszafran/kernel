#include <stdint.h>

void outb(uint16_t port, uint8_t value)
{
    __asm__ __volatile__("outb %1, %0" : : "dN" (port), "a" (value));
}

void outw(uint16_t port, uint16_t value)
{
    __asm__ __volatile__("outw %1, %0" : : "dN" (port), "a" (value));
}

void outl(uint16_t port, uint32_t value)
{
    __asm__ __volatile__("outl %1, %0" : : "dN" (port), "a" (value));
}

uint8_t inb(uint16_t port)
{
    uint8_t ret;

    __asm__ __volatile__("inb %1, %0"
        : "=a" (ret)
        : "dN" (port));

    return ret;
}

uint16_t inw(uint16_t port)
{
    uint16_t ret;

    __asm__ __volatile__("inw %1, %0"
        : "=a" (ret)
        : "dN" (port));

    return ret;
}

uint32_t inl(uint16_t port)
{
    uint32_t ret;

    __asm__ __volatile__("inl %1, %0"
        : "=a" (ret)
        : "dN" (port));

    return ret;
}

void io_wait(void)
{
    __asm__ __volatile__("outb %%al, $0x80"
            : : "a"(0) );
}