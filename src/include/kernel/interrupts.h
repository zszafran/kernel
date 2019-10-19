#pragma once

#include <stdint.h>

typedef struct registers {
   uintptr_t ds;
   uintptr_t edi;
   uintptr_t esi;
   uintptr_t ebp;
   uintptr_t esp;
   uintptr_t ebx;
   uintptr_t edx;
   uintptr_t ecx;
   uintptr_t eax;
   uintptr_t int_no;
   uintptr_t err_code;
   uintptr_t eip;
   uintptr_t cs;
   uintptr_t eflags;
   uintptr_t useresp;
   uintptr_t ss;
} registers_t;

typedef void (*isr_t)(struct registers *);

void register_interrupt_handler(uint16_t n, isr_t handler);