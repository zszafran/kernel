#include <stdio.h>
#include <stdint.h>

#include <kernel/tty.h>
#include <kernel/log.h>
#include <boot/gdt.h>
#include <boot/idt.h>
#include <boot/multiboot2_info.h>

multiboot_info_t boot_info;

void kernel_main(void) {
	read_multiboot(&boot_info);

	terminal_initialize(
		boot_info.framebuffer_tag->common.framebuffer_addr,
      	boot_info.framebuffer_tag->common.framebuffer_width,
      	boot_info.framebuffer_tag->common.framebuffer_height);

	init_gdt();
	init_idt();

	log("Boot Info:");

  	log("\tCommand line = %s", boot_info.command_line_tag->string);

  	log("\tBoot loader name = %s", boot_info.boot_loader_name_tag->string);

  	log("\tmem_lower = %uKB, mem_upper = %uKB",
      	boot_info.basic_meminfo_tag->mem_lower,
      	boot_info.basic_meminfo_tag->mem_upper);

  	log("\tBoot device 0x%x,%u,%u",
      	boot_info.boot_device_tag->biosdev,
      	boot_info.boot_device_tag->slice,
      	boot_info.boot_device_tag->part);

  	if (boot_info.memory_map_tag)
  	{
    	int entry_count = boot_info.memory_map_tag->size / boot_info.memory_map_tag->entry_size;
    	log("\tMemory Map: numEntries=0x%x", entry_count);

    	multiboot_memory_map_t *mmap;
    	for (int i = 0; i < entry_count; i++)
    	{
      		mmap = (multiboot_memory_map_t *)((uint8_t *)boot_info.memory_map_tag->entries + (i * boot_info.memory_map_tag->entry_size));
      		log("\t\tbase_addr = 0x%x%x, length = 0x%x%x, type = 0x%x",
          		(unsigned)(mmap->addr >> 32),
          		(unsigned)(mmap->addr & 0xffffffff),
          		(unsigned)(mmap->len >> 32),
          		(unsigned)(mmap->len & 0xffffffff),
          		(unsigned)mmap->type);
    	}
  	}

  	if (boot_info.framebuffer_tag)
  	{
    	log("\tFramebuffer: addr = 0x%x, type = 0x%x",
        	boot_info.framebuffer_tag->common.framebuffer_addr,
        	boot_info.framebuffer_tag->common.framebuffer_type);
    	log("\t\twidth = 0x%x, height = 0x%x, pitch = 0x%x, colors = 0x%x",
        	boot_info.framebuffer_tag->common.framebuffer_width,
        	boot_info.framebuffer_tag->common.framebuffer_height,
        	boot_info.framebuffer_tag->common.framebuffer_pitch,
        	boot_info.framebuffer_tag->framebuffer_palette_num_colors);
  	}

  	log("\tMultiboot: start = 0x%x, end = 0x%x",
      	boot_info.multiboot_start,
      	boot_info.multiboot_end);

	debug("Hello, kernel World!");

	asm volatile ("int $0x3");
	asm volatile ("int $0x4");

	while(1) __asm__ volatile ("hlt");
}