#include <memory.h>
#include <stdbool.h>
#include <stdint.h>

static uint64_t u(void *val) { // Convert to uint64_t
    return (uint64_t) val; // Saves me a bit of work
}

static void* to_hh(void *low) { // To higher-half address
    return (void*) (((uint64_t) low) | 0xffff800000000000);
}

static bool can_map_page(uint64_t vaddr) {
    PML4T *pml4t = to_hh(read_cr3());
    if(!(u(pml4t) & 1)) return 0;
    pml4t = (void*) (u(pml4t) & 0xfffffffffffff000);
    PDPT *pml4e = to_hh(pml4t->pdpt[(vaddr >> 39) & 0x1ff]);
    if(!(u(pml4e) & 1)) return 0;
    pml4e = (void*) (u(pml4e) & 0xfffffffffffff000);
    PDT *pdpe = to_hh(pml4e->pdt[(vaddr >> 30) & 0x1ff]);
    if(!(u(pdpe) & 1)) return 0;
    pdpe = (void*) (u(pdpe) & 0xfffffffffffff000);
    PT *pde = to_hh(pdpe->pt[(vaddr >> 21) & 0x1ff]);
    if(!(u(pde) & 1)) return 0;
    pde = (void*) (u(pde) & 0xfffffffffffff000);
    void *pte = pde->pe[(vaddr >> 12) & 0x1ff];
    if(u(pte) & 1) return 0;
    return 1;
}

static bool can_map_pages(uint64_t vaddr, size_t pcount) {
    for(size_t i = 0; i < pcount; i++) {
        if(!can_map_page(vaddr+i*0x1000)) return 0;
    }
    return 1;
}

static void map_page(void *__physical paddr, uint64_t vaddr) {
    PML4T *pml4t = to_hh(read_cr3());
    pml4t = (void*) (u(pml4t) & 0xfffffffffffff000);
    pml4t->pdpt[(vaddr >> 39) & 0x1ff] = (void*) (u(pml4t->pdpt[(vaddr >> 39) & 0x1ff]) | 1);
    PDPT *pml4e = to_hh(pml4t->pdpt[(vaddr >> 39) & 0x1ff]);
    pml4e = (void*) (u(pml4e) & 0xfffffffffffff000);
    pml4e->pdt[(vaddr >> 30) & 0x1ff] = (void*) (u(pml4e->pdt[(vaddr >> 30) & 0x1ff]) | 1);
    PDT *pdpe = to_hh(pml4e->pdt[(vaddr >> 30) & 0x1ff]);
    pdpe = (void*) (u(pdpe) & 0xfffffffffffff000);
    pdpe->pt[(vaddr >> 21) & 0x1ff] = (void*) (u(pdpe->pt[(vaddr >> 21) & 0x1ff]) | 1);
    PT *pde = to_hh(pdpe->pt[(vaddr >> 21) & 0x1ff]);
    pde = (void*) (u(pde) & 0xfffffffffffff000);
    pde->pe[(vaddr >> 12) & 0x1ff] = (void*) (u(paddr) | 1);
}

static void kmap_real(void *__physical paddr, uint64_t vaddr, size_t pcount) {
    for(size_t i = 0; i < pcount; i++) map_page(paddr+i*0x1000, vaddr+i*0x1000);
}

// \brief Map memory, intended for use in the kernel
// \param paddr The physical address to be mapped into virtual space
// \param vaddr_hint The target page to map
// \param pcount The number of pages to be mapped
// \return The virtual address that actually got mapped
// No, I don't care that this is incredibly inefficient. It's meant to be readable; it's not unreasonable for us to go back and rewrite this later.
void* kmap(void *__physical paddr, void *vaddr_hint, size_t pcount) {
    uint64_t vaddr = u(vaddr_hint) & 0xffffffffffff000;
    while(!can_map_pages(vaddr, pcount)) vaddr += 0x1000;
    kmap_real(paddr, vaddr, pcount);
    return (void*) vaddr;
}
