#include <memory.h>
#include <stdint.h>

// \brief Map memory, intended for use in the kernel
// \param paddr The physical address to be mapped into virtual space
// \param vaddr_hint A potential address within the target page
// \param pcount The number of pages to be mapped
// \return The virtual address that actually got mapped
void* kmap(void *__physical paddr, void *vaddr_hint, size_t pcount) {
    PML4T *pml4t = (PML4T*) (((uint64_t) read_cr3()) | 0xffff800000000000); // Translate into higher-half
    uint64_t vaddr = ((uint64_t) vaddr_hint) & 0xffffffffffff000;
    PDPT *pml4e = pml4t->pdpt[(vaddr >> 39) & 0x1ff];
    PDT *pdpe = pml4e->pdt[(vaddr >> 30) & 0x1ff];
    PT *pde = pdpe->pt[(vaddr >> 21) & 0x1ff];
    for(size_t i = 0; i < pcount; i++)
        pde->pe[((vaddr >> 12) & 0x1ff) + i] = paddr;
    return (void*) vaddr;
}
