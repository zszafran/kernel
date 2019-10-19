#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <kernel/log.h>
#include <kernel/multiboot2.h>

void read_multiboot(uintptr_t multiboot_ptr, multiboot_info_t *mbi)
{
  	if (multiboot_ptr & 7)
  	{
    	panic("Multiboot unaligned mbi");
  	}

  	mbi->multiboot_start = multiboot_ptr;

  	// skip 8 because the magic number is stored there
  	struct multiboot_tag *tag = (struct multiboot_tag *)((uintptr_t)(multiboot_ptr + 8));

  	while (tag->type != MULTIBOOT_TAG_TYPE_END)
  	{
    	switch (tag->type)
    	{
    		case MULTIBOOT_TAG_TYPE_CMDLINE:
      			mbi->command_line_tag = (struct multiboot_tag_string *)tag;
      			break;

    		case MULTIBOOT_TAG_TYPE_BOOT_LOADER_NAME:
      			mbi->boot_loader_name_tag = (struct multiboot_tag_string *)tag;
      			break;

			case MULTIBOOT_TAG_TYPE_BASIC_MEMINFO:
				mbi->basic_meminfo_tag = (struct multiboot_tag_basic_meminfo *)tag;
				break;

			case MULTIBOOT_TAG_TYPE_BOOTDEV:
				mbi->boot_device_tag = (struct multiboot_tag_bootdev *)tag;
				break;

			case MULTIBOOT_TAG_TYPE_MMAP:
				mbi->memory_map_tag = (struct multiboot_tag_mmap *)tag;
				break;

			case MULTIBOOT_TAG_TYPE_ACPI_NEW:
				mbi->new_acpi_tag = (struct multiboot_tag_new_acpi *)tag;
				break;

			case MULTIBOOT_TAG_TYPE_ACPI_OLD:
				mbi->old_acpi_tag = (struct multiboot_tag_old_acpi *)tag;
				break;

			case MULTIBOOT_TAG_TYPE_SMBIOS:
				mbi->smbios_tag = (struct multiboot_tag_smbios *)tag;
				break;

			case MULTIBOOT_TAG_TYPE_ELF_SECTIONS:
				mbi->elf_sections_tag = (struct multiboot_tag_elf_sections *)tag;
				break;

			case MULTIBOOT_TAG_TYPE_FRAMEBUFFER:
				mbi->framebuffer_tag = (struct multiboot_tag_framebuffer *)tag;
				break;

			case MULTIBOOT_TAG_TYPE_MODULE:
				mbi->module_tag = (struct multiboot_tag_module *)tag;
				break;
		}

		tag = (struct multiboot_tag *)((uint8_t *)tag + ((tag->size + 7) & ~7));
	}

  mbi->end_tag = tag;
  mbi->multiboot_end = (uintptr_t)(tag + tag->size);
}

void print_multiboot(multiboot_info_t *mbi)
{
	debug("Multiboot Info:");

  	debug("\tCommand line = %s", mbi->command_line_tag->string);

  	debug("\tBoot loader name = %s", mbi->boot_loader_name_tag->string);

  	debug("\tmem_lower = %uKB, mem_upper = %uKB",
      	mbi->basic_meminfo_tag->mem_lower,
      	mbi->basic_meminfo_tag->mem_upper);

  	debug("\tBoot device 0x%x,%u,%u",
      	mbi->boot_device_tag->biosdev,
      	mbi->boot_device_tag->slice,
      	mbi->boot_device_tag->part);

  	if (mbi->memory_map_tag)
  	{
    	int entry_count = mbi->memory_map_tag->size / mbi->memory_map_tag->entry_size;
    	debug("\tMemory Map: numEntries=0x%x", entry_count);

    	multiboot_memory_map_t *mmap;
    	for (int i = 0; i < entry_count; i++)
    	{
      		mmap = (multiboot_memory_map_t *)((uint8_t *)mbi->memory_map_tag->entries + (i * mbi->memory_map_tag->entry_size));
      		debug("\t\tbase_addr = 0x%x%x, length = 0x%x%x, type = 0x%x",
          		(unsigned)(mmap->addr >> 32),
          		(unsigned)(mmap->addr & 0xffffffff),
          		(unsigned)(mmap->len >> 32),
          		(unsigned)(mmap->len & 0xffffffff),
          		(unsigned)mmap->type);
    	}
  	}

  	if (mbi->framebuffer_tag)
  	{
    	debug("\tFramebuffer: addr = 0x%x, type = 0x%x",
        	mbi->framebuffer_tag->common.framebuffer_addr,
        	mbi->framebuffer_tag->common.framebuffer_type);
    	debug("\t\twidth = 0x%x, height = 0x%x, pitch = 0x%x, colors = 0x%x",
        	mbi->framebuffer_tag->common.framebuffer_width,
        	mbi->framebuffer_tag->common.framebuffer_height,
        	mbi->framebuffer_tag->common.framebuffer_pitch,
        	mbi->framebuffer_tag->framebuffer_palette_num_colors);
  	}

  	debug("\tMultiboot: start = 0x%x, end = 0x%x",
      	mbi->multiboot_start,
      	mbi->multiboot_end);
}