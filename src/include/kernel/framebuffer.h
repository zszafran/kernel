#pragma once

#include <stddef.h>
#include <stdint.h>

void init_framebuffer(uintptr_t framebuffer_addr,
                      unsigned int width,
                      unsigned int height);
void clear_framebuffer(void);
void shiftup_framebuffer(void);
void setcolor_framebuffer(uint8_t color);
void putentryat_framebuffer(unsigned char c, uint8_t color, size_t x, size_t y);
void putchar_framebuffer(char c);
void write_framebuffer(const char *data, size_t size);
void writestring_framebuffer(const char *data);