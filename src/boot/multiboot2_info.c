#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <boot/multiboot2.h>
#include <boot/multiboot2_info.h>

extern const uintptr_t multiboot_ptr;
extern const uint32_t multiboot_magic;

void read_multiboot(multiboot_info_t *self)
{
  	if (multiboot_magic != MULTIBOOT2_BOOTLOADER_MAGIC)
  	{
    	panic("Invalid multiboot magic number");
  	}

  	if (multiboot_ptr & 7)
  	{
    	panic("Multiboot unaligned mb");
  	}

  	self->multiboot_start = multiboot_ptr;

  	// skip 8 because the magic number is stored there
  	struct multiboot_tag *tag = (struct multiboot_tag *)((uintptr_t)(multiboot_ptr + 8));

  	while (tag->type != MULTIBOOT_TAG_TYPE_END)
  	{
    	switch (tag->type)
    	{
    		case MULTIBOOT_TAG_TYPE_CMDLINE:
      			self->command_line_tag = (struct multiboot_tag_string *)tag;
      			break;

    		case MULTIBOOT_TAG_TYPE_BOOT_LOADER_NAME:
      			self->boot_loader_name_tag = (struct multiboot_tag_string *)tag;
      			break;

			case MULTIBOOT_TAG_TYPE_BASIC_MEMINFO:
				self->basic_meminfo_tag = (struct multiboot_tag_basic_meminfo *)tag;
				break;

			case MULTIBOOT_TAG_TYPE_BOOTDEV:
				self->boot_device_tag = (struct multiboot_tag_bootdev *)tag;
				break;

			case MULTIBOOT_TAG_TYPE_MMAP:
				self->memory_map_tag = (struct multiboot_tag_mmap *)tag;
				break;

			case MULTIBOOT_TAG_TYPE_ACPI_NEW:
				self->new_acpi_tag = (struct multiboot_tag_new_acpi *)tag;
				break;

			case MULTIBOOT_TAG_TYPE_ACPI_OLD:
				self->old_acpi_tag = (struct multiboot_tag_old_acpi *)tag;
				break;

			case MULTIBOOT_TAG_TYPE_SMBIOS:
				self->smbios_tag = (struct multiboot_tag_smbios *)tag;
				break;

			case MULTIBOOT_TAG_TYPE_ELF_SECTIONS:
				self->elf_sections_tag = (struct multiboot_tag_elf_sections *)tag;
				break;

			case MULTIBOOT_TAG_TYPE_FRAMEBUFFER:
				self->framebuffer_tag = (struct multiboot_tag_framebuffer *)tag;
				break;

			case MULTIBOOT_TAG_TYPE_MODULE:
				self->module_tag = (struct multiboot_tag_module *)tag;
				break;
		}

		tag = (struct multiboot_tag *)((uint8_t *)tag + ((tag->size + 7) & ~7));
	}

  self->end_tag = tag;
  self->multiboot_end = (uintptr_t)(tag + tag->size);
}