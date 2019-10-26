#pragma once

#define KERNEL_PHYSICAL_OFFSET 0x40000000
#define KERNEL_PHYSICAL_ADDR 0x100000

#define KERNEL_VIRTUAL_OFFSET 0xC0000000
#define KERNEL_VIRTUAL_ADDR KERNEL_PHYSICAL_ADDR + KERNEL_VIRTUAL_OFFSET

#define VIRT_TO_PHYS_ADDR(addr) ((addr) - KERNEL_VIRTUAL_OFFSET)
#define PHYS_TO_VIRT_ADDR(addr) ((addr) + KERNEL_VIRTUAL_OFFSET)

#ifndef LINKER_FILE

#include <stdint.h>

extern uint32_t _KERNEL_START;
extern uint32_t _KERNEL_END;

extern uint32_t _TEXT_START;
extern uint32_t _TEXT_END;

extern uint32_t _RODATA_START;
extern uint32_t _RODATA_END;

extern uint32_t _DATA_START;
extern uint32_t _DATA_END;

extern uint32_t _BBS_START;
extern uint32_t _BBS_END;

extern void cpu_idle(void);

#endif /*  ! LINKER_FILE */