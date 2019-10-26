#pragma once

#include <stdint.h>

/**
 * Allocate a chunk of memory, sz in size. If align == 1,
 * the chunk must be page-aligned. If phys != 0, the physical
 * location of the allocated chunk will be stored into phys.
 * This is the internal version of kmalloc. More user-friendly
 * parameter representations are available in kmalloc, kmalloc_a,
 * kmalloc_ap, kmalloc_p.
 */
uintptr_t kmalloc_internal(uint32_t sz, int align, uintptr_t *phys);

/**
 * Allocate a chunk of memory, sz in size. The chunk must be
 * page aligned.
 */
uintptr_t kmalloc_a(uint32_t sz);

/**
 * Allocate a chunk of memory, sz in size. The physical address
 * is returned in phys. Phys MUST be a valid pointer to uint32_t!
 */
uintptr_t kmalloc_p(uint32_t sz, uintptr_t *phys);

/**
 * Allocate a chunk of memory, sz in size. The physical address 
 * is returned in phys. It must be page-aligned.
 */
uintptr_t kmalloc_ap(uint32_t sz, uintptr_t *phys);

/**
 * General allocation function.
 */
uintptr_t kmalloc(uint32_t sz);