#include <stdint.h>
#include <kernel/kernel.h>
#include <kernel/kheap.h>

uintptr_t placement_address = (uintptr_t)&_KERNEL_END;

uintptr_t kmalloc_internal(uint32_t sz, int align, uintptr_t *phys)
{
	// This will eventually call malloc() on the kernel heap.
    // For now, though, we just assign memory at placement_address
    // and increment it by sz. Even when we've coded our kernel
    // heap, this will be useful for use before the heap is initialised.
    if (align == 1 && (placement_address & 0xFFFFF000) )
    {
        // Align the placement address;
        placement_address &= 0xFFFFF000;
        placement_address += 0x1000;
    }
    if (phys)
    {
        *phys = placement_address;
    }
    uintptr_t tmp = placement_address;
    placement_address += sz;
    return tmp;
}

uintptr_t kmalloc_a(uint32_t sz)
{
    return kmalloc_internal(sz, 1, 0);
}

uintptr_t kmalloc_p(uint32_t sz, uintptr_t *phys)
{
    return kmalloc_internal(sz, 0, phys);
}

uintptr_t kmalloc_ap(uint32_t sz, uintptr_t *phys)
{
    return kmalloc_internal(sz, 1, phys);
}

uintptr_t kmalloc(uint32_t sz)
{
    return kmalloc_internal(sz, 0, 0);
}