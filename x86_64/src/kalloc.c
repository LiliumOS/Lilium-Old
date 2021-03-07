#include <stdbool.h>
#include "memory.h"

extern void *__heap;

typedef struct alloc_header {
    size_t size; // Low bit = occupied
    struct alloc_header *prev;
    struct alloc_header *next;
} alloc_header;

void* kalloc(size_t size, size_t alignment, enum MemoryPool pool) {
    static bool heap_initialized = 0;
    if(!heap_initialized) {
        alloc_header *hdr = (alloc_header*) __heap; // The top of the heap is its own block
        hdr->size = 0x100000 - (uint64_t) __heap - sizeof(alloc_header); // I don't know how much memory we have :)
        hdr->prev = NULL; // Nothing before the first block
        hdr->next = NULL; // Nothing after the last block
    }

    if(pool != KERNEL) return NULL; // Don't have support for anything else yet

    if(!size) return NULL; // You can't allocate with no size, dummy
    size++; size |= 1; // Fun math.
    // So, we need to round size up to the nearest multiple of 2, then set the low bit.
    // 00 ->  01 ->  01
    // 01 ->  10 ->  11
    // 10 ->  11 ->  11
    // 11 -> 100 -> 101
    // Easy enough ;)

    if(alignment < sizeof(uint64_t)) alignment = sizeof(uint64_t); // Default alignment, and the only minimum alignment that makes the allocator remotely efficient
    // And then we're going to ignore alignment. For now. FIXME.

    alloc_header *hdr = (alloc_header*) __heap;
    do {
        if(hdr->size >= (size & (~1))) break;
    } while((hdr = hdr->next));
    if(!hdr) return NULL; // Sorry, we're full.
    size_t prev_size = hdr->size;
    alloc_header *next = hdr->next;
    hdr->size = size;
    alloc_header *next_hdr = (alloc_header*) (((uint64_t) hdr) + sizeof(alloc_header) + (size & ~1));
    if((size & ~1) > (prev_size-sizeof(alloc_header)+2)) {
        // We have space for more. Woo.
        next_hdr->size = prev_size - sizeof(alloc_header) - (size & ~1);
        next_hdr->prev = hdr;
        next_hdr->next = next;
    } // If we don't have space for more, the pointers will already be correct.
    return (void*) (hdr + 1);
}
