#pragma once

#include <stdint.h>

typedef struct page
{
    uint32_t present    : 1;   // Page present in memory
    uint32_t rw         : 1;   // Read-only if clear, readwrite if set
    uint32_t user       : 1;   // Supervisor level only if clear
    uint32_t accessed   : 1;   // Has the page been accessed since last refresh?
    uint32_t dirty      : 1;   // Has the page been written to since last refresh?
    uint32_t unused     : 7;   // Amalgamation of unused and reserved bits
    uint32_t frame      : 20;  // Frame address (shifted right 12 bits)
} page_t;

typedef struct page_table
{
    page_t pages[1024];
} page_table_t;

typedef struct page_directory
{
    /** Array of pointers to pagetables. */
    page_table_t *tables[1024];
    /**
     * Array of pointers to the pagetables above, but gives their *physical*
     * location, for loading into the CR3 register.
     */
    uintptr_t tablesPhysical[1024];
    /**
     * The physical address of tablesPhysical. This comes into play
     * when we get our kernel heap allocated and the directory
     * may be in a different location in virtual memory.
     **/
    uintptr_t physicalAddr;
} page_directory_t;

extern void load_page_directory(uintptr_t* pt);
extern void enable_paging();
extern void disable_paging();

void init_paging();
void alloc_frame(page_t *page, int is_kernel, int is_writeable);
void free_frame(page_t *page);
page_t *get_page(uint32_t address, int make, page_directory_t *dir);