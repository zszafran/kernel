#include <stdio.h>
#include <stdint.h>

#include <kernel/tty.h>
#include <kernel/log.h>
#include <boot/multiboot2_info.h>;

multiboot_info_t boot_info;

void kernel_main(void) {
	read_multiboot(&boot_info);
	terminal_initialize(
		boot_info.framebuffer_tag->common.framebuffer_addr,
      	boot_info.framebuffer_tag->common.framebuffer_width,
      	boot_info.framebuffer_tag->common.framebuffer_height);
	log("Booting...");
	print_boot_info(&boot_info);
	debug("Hello, kernel World!");
}

void print_boot_info(multiboot_info_t *self)
{
  	log("Boot Info:");

  	log("\tCommand line = %s", self->command_line_tag->string);

  	log("\tBoot loader name = %s", self->boot_loader_name_tag->string);

  	log("\tModule at 0x%x-0x%x. Command line %s",
      	self->module_tag->mod_start,
      	self->module_tag->mod_end,
      	self->module_tag->cmdline);

  	log("\tmem_lower = %uKB, mem_upper = %uKB",
      	self->basic_meminfo_tag->mem_lower,
      	self->basic_meminfo_tag->mem_upper);

  	log("\tBoot device 0x%x,%u,%u",
      	self->boot_device_tag->biosdev,
      	self->boot_device_tag->slice,
      	self->boot_device_tag->part);

  	if (self->memory_map_tag)
  	{
    	int entry_count = self->memory_map_tag->size / self->memory_map_tag->entry_size;
    	log("\tMemory Map: numEntries=0x%x", entry_count);

    	multiboot_memory_map_t *mmap;
    	for (int i = 0; i < entry_count; i++)
    	{
      		mmap = (multiboot_memory_map_t *)((uint8_t *)self->memory_map_tag->entries + (i * self->memory_map_tag->entry_size));
      		log("\t\tbase_addr = 0x%x%x, length = 0x%x%x, type = 0x%x",
          		(unsigned)(mmap->addr >> 32),
          		(unsigned)(mmap->addr & 0xffffffff),
          		(unsigned)(mmap->len >> 32),
          		(unsigned)(mmap->len & 0xffffffff),
          		(unsigned)mmap->type);
    	}
  	}

  	if (self->framebuffer_tag)
  	{
    	log("\tFramebuffer: addr = 0x%x, type = 0x%x",
        	self->framebuffer_tag->common.framebuffer_addr,
        	self->framebuffer_tag->common.framebuffer_type);
    	log("\t\twidth = 0x%x, height = 0x%x, pitch = 0x%x, colors = 0x%x",
        	self->framebuffer_tag->common.framebuffer_width,
        	self->framebuffer_tag->common.framebuffer_height,
        	self->framebuffer_tag->common.framebuffer_pitch,
        	self->framebuffer_tag->framebuffer_palette_num_colors);
  	}

  	log("\tMultiboot: start = 0x%x, end = 0x%x",
      	self->multiboot_start,
      	self->multiboot_end);
}