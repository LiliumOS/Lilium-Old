// memory.h
// 
// This file is part of PhantomOS.
//
// PhantomOS is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// PhantomOS is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with PhantomOS.  If not, see <https://www.gnu.org/licenses/>.
//
// PhantomOS is additionally distributed with a system call exemption
// As an exeption to the above license, 
//  proprietary software may interface with this software through the use of 
//  "system calls" to access any of the routines made available by the PhantomOS 
//  to programs written to be employed by the user.

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
