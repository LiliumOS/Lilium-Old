//
// Created by chorm on 2020-09-05.
//

#ifndef PHANTOMOS_MEMORY_H
#define PHANTOMOS_MEMORY_H

typedef struct PML5T{
    uint64_t pml4t[512];
}__attribute__((align(4096))) PML5T;

typedef struct PML4T{
    uint64_t pdpt[512];
}__attribute__((align(4096))) PML4T;

typedef struct PDPT{
    uint64_t pdt[512];
}__attribute__((align(4096))) PDPT;

typedef struct PPT{
    uint64_t pt[512];
}__attribute__((align(4096))) PPT;

typedef struct PT{
    uint64_t pe[512];
}__attribute__((align(4096))) PT;

void* get_mapped_virtual_address(void* paddr);

void* get_mapped_physical_addr(void* vaddr);

#endif //PHANTOMOS_MEMORY_H
