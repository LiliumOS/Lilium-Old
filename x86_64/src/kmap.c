#include <memory.h>
#include <stdint.h>

static void* to_hh(void *low) { // To higher-half address
    return (void*) (((uint64_t) low) | 0xffff800000000000);
}

static bool can_map_page(uint64_t vaddr) {
    PML4T *pml4t = to_hh(read_cr3());
    pml4t = (void*) (((uint64_t) pml4t) & 0xfffffffffffff000);
    PDPT *pml4e = to_hh(pml4t->pdpt[(vaddr >> 39) & 0x1ff]);
    pml4e = (void*) (((uint64_t) pml4e) & 0xfffffffffffff000);
    PDT *pdpe = to_hh(pml4e->pdt[(vaddr >> 30) & 0x1ff]);
    pdpe = (void*) (((uint64_t) pdpe) & 0xfffffffffffff000);
    PT *pde = to_hh(pdpe->pt[(vaddr >> 21) & 0x1ff]);
    pde = (void*) (((uint64_t) pde) & 0xfffffffffffff000);
    void *pte = pde->pe[(vaddr >> 12) & 0x1ff];
    if(pte & 1) return 0;
    return 1;
}

static bool can_map_pages(uint64_t vaddr, size_t pcount) {
    for(size_t i = 0; i < pcount; i++) {
        if(!can_map_page(vaddr)) return 0;
    }
    return 1;
}

static void map_page(void *__physical paddr, uint64_t vaddr) {
    PML4T *pml4t = to_hh(read_cr3());
    pml4t = (void*) (((uint64_t) pml4t) & 0xfffffffffffff000);
    pml4t->pdpt[(vaddr >> 39) & 0x1ff] |= 1;
    PDPT *pml4e = to_hh(pml4t->pdpt[(vaddr >> 39) & 0x1ff]);
    pml4e = (void*) (((uint64_t) pml4e) & 0xfffffffffffff000);
    pml4e->pdt[(vaddr >> 30) & 0x1ff] |= 1;
    PDT *pdpe = to_hh(pml4e->pdt[(vaddr >> 30) & 0x1ff]);
    pdpe = (void*) (((uint64_t) pdpe) & 0xfffffffffffff000);
    pdpe->pt[(vaddr >> 21) & 0x1ff] |= 1;
    PT *pde = to_hh(pdpe->pt[(vaddr >> 21) & 0x1ff]);
    pde = (void*) (((uint64_t) pde) & 0xfffffffffffff000);
    pde->pt[(vaddr >> 12) & 0x1ff] |= 1;
    pde->pe[(vaddr >> 12) & 0x1ff] = paddr | 1;
}

static void kmap_real(void *__physical paddr, uint64_t vaddr, size_t pcount) {
    for(size_t i = 0; i < pcount; i++) map_page(paddr, vaddr);
}

// \brief Map memory, intended for use in the kernel
// \param paddr The physical address to be mapped into virtual space
// \param vaddr_hint The target page to map
// \param pcount The number of pages to be mapped
// \return The virtual address that actually got mapped
// No, I don't care that this is incredibly inefficient. It's meant to be readable; it's not unreasonable for us to go back and rewrite this later.
void* kmap(void *__physical paddr, void *vaddr_hint, size_t pcount) {
    uint64_t vaddr = ((uint64_t) vaddr_hint) & 0xffffffffffff000;
    while(!can_map_pages(vaddr)) vaddr += 0x1000;
    kmap_real(paddr, vaddr, pcount);
    return (void*) vaddr;
}
