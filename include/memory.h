//
// Created by chorm on 2020-09-05.
//

#ifndef PHANTOMOS_MEMORY_H
#define PHANTOMOS_MEMORY_H

#include <stdint.h>
#include <stddef.h>


typedef struct PML5T{
    _Alignas(4096) int64_t pml4t[512];
} PML5T;

typedef struct PML4T{
    _Alignas(4096) int64_t pdpt[512];
} PML4T;

typedef struct PDPT{
    _Alignas(4096) int64_t pdt[512];
} PDPT;

typedef struct PDT{
    _Alignas(4096) int64_t pt[512];
} PPT;

typedef struct PT{
    _Alignas(4096) int64_t pe[512];
} PT;

void* get_mapped_virtual_address(int64_t paddr);

int64_t get_mapped_physical_addr(void* vaddr);

int64_t read_cr3();


void* kmap(int64_t paddr,void* vaddr_hint,size_t pcount);

#endif //PHANTOMOS_MEMORY_H
