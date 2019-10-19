#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <kernel/ansi.h>
#include <kernel/framebuffer.h>
#include <kernel/multiboot2.h>
#include <kernel/vga.h>

static size_t terminal_width = 80;
static size_t terminal_height = 25;
static size_t terminal_row = 0;
static size_t terminal_column = 0;
static uint8_t terminal_color;
static uint16_t *terminal_buffer = FRAMEBUFFER_ADDR;
static struct ansi_state terminal_color_state;

void init_framebuffer(multiboot_info_t* mbi)
{
	multiboot_tag_framebuffer_t* fb_tag = get_multiboot_framebuffer_tag(mbi);

	if (!fb_tag) {
		panic("Unable to initialize framebuffer, tag not found in MBI.");
	}

  	terminal_width = fb_tag->common.framebuffer_width;
	terminal_height = fb_tag->common.framebuffer_height;
	terminal_buffer = (uint16_t*)fb_tag->common.framebuffer_addr;
  	terminal_row = 0;
  	terminal_column = 0;
  	terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
  	terminal_color_state = ansi_init();
}

void clear_framebuffer()
{
	for (size_t y = 0; y < terminal_height; y++)
  	{
    	for (size_t x = 0; x < terminal_width; x++)
    	{
      		const size_t index = y * terminal_width + x;
      		terminal_buffer[index] = vga_entry(' ', terminal_color);
    	}
  	}
}

void shiftup_framebuffer()
{
  	for (size_t y = 0; y < terminal_height - 1; y++)
  	{
    	for (size_t x = 0; x < terminal_width; x++)
    	{
      		const size_t target = y * terminal_width + x;
      		const size_t source = (y + 1) * terminal_width + x;
      		terminal_buffer[target] = terminal_buffer[source];
    	}
  	}
  	for (size_t x = 0; x < terminal_width; x++)
  	{
    	const size_t index = (terminal_height - 1) * terminal_width + x;
    	terminal_buffer[index] = vga_entry(' ', terminal_color);
  	}
}

void setcolor_framebuffer(uint8_t color)
{
  	terminal_color = color;
}

void putentryat_framebuffer(unsigned char c, uint8_t color, size_t x, size_t y)
{
  	const size_t index = y * terminal_width + x;
  	terminal_buffer[index] = vga_entry(c, color);
}

void putchar_framebuffer(char c)
{
  	unsigned char uc = c;

  	if (uc == '\n')
  	{
    	terminal_column = 0;
    	terminal_row++;
    	return;
  	}

  	if (uc == '\t')
  	{
    	terminal_column += 2;
    	return;
  	}

  	if (terminal_row == terminal_height)
  	{
    	shiftup_framebuffer();
    	terminal_row = terminal_height - 1;
  	}

  	putentryat_framebuffer(uc, terminal_color, terminal_column, terminal_row);

  	if (++terminal_column == terminal_width)
  	{
    	terminal_column = 0;
    	++terminal_row;
  	}
}

void write_framebuffer(const char *data, size_t size)
{
  	for (size_t i = 0; i < size; i++)
  	{
    	struct ansi_color_char color_char = ansi_process(&terminal_color_state, data[i]);
    	if (color_char.ascii != '\0')
    	{
      		setcolor_framebuffer(color_char.color);
      		putchar_framebuffer(color_char.ascii);
    	}
  	}
}

void writestring_framebuffer(const char *data)
{
  	write_framebuffer(data, strlen(data));
}