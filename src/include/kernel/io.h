#pragma once

#include <stdint.h>

void outb(uint16_t port,  uint8_t byte);
void outw(uint16_t port, uint16_t word);
void outl(uint16_t port, uint32_t word);

uint32_t inl(uint16_t port);
uint16_t inw(uint16_t port);
uint8_t inb(uint16_t port);

void io_wait(void);