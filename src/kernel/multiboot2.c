#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <kernel/log.h>
#include <kernel/multiboot2.h>

multiboot_tag_t* get_multiboot_tag(multiboot_tag_t *tags, uint16_t type)
{
    multiboot_tag_t *tag;

    for (
        tag = tags; // points to the first tag of the multiboot_info_t struct
        tag->type != MULTIBOOT_TAG_TYPE_END;
        tag = (multiboot_tag_t *) ((uint8_t *) tag + ((tag->size + 7) & ~7))
    ) {
        if (tag->type == type) {
            return tag;
        }
    }

    return 0;
}

multiboot_tag_framebuffer_t* get_multiboot_framebuffer_tag(multiboot_info_t *mbi)
{
	return (multiboot_tag_framebuffer_t*) get_multiboot_tag(
		mbi->tags, MULTIBOOT_TAG_TYPE_FRAMEBUFFER);
}