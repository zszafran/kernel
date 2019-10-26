ENTRY(_start)

#define LINKER_FILE 1
#include <kernel/kernel.h>

#define SECTION(name) \
    name BLOCK(4K) : ALIGN(4K)

#define DEFINE_START(name) \
    _##name##_START = ABSOLUTE(.);

#define DEFINE_END(name) \
    _##name##_END = ABSOLUTE(.);

SECTIONS
{
	. = KERNEL_PHYSICAL_ADDR;

	DEFINE_START(KERNEL)
 
	SECTION(.text)
	{
		DEFINE_START(TEXT)
		KEEP(*(.multiboot))
		*(.multiboot.info)
		*(.text)
		DEFINE_END(TEXT)
	}
 
	SECTION(.rodata)
	{
		DEFINE_START(RODATA)
		*(.rodata)
		*(.rodata.*)
		DEFINE_END(RODATA)
	}
 
	SECTION(.data)
	{
		DEFINE_START(DATA)
		*(.data)
		DEFINE_END(DATA)
	}

	SECTION(.eh_frame)
	{
		DEFINE_START(EHFRAME)
		*(.eh_frame)
		DEFINE_END(EHFRAME)
	}
 
	SECTION(.bss)
	{
		DEFINE_START(BBS)
		*(COMMON)
		*(.bss)
		DEFINE_END(BBS)
	}

	DEFINE_END(KERNEL)
 
	/DISCARD/ :
    {
		*(.comment)
   	}
}