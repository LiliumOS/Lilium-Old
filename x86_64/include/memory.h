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

#define __kernel
#define __user
#define __mixed
#define __physical

typedef struct PT{
    _Alignas(4096) void* __physical pe[512];
} PT;

typedef struct PDT{
    _Alignas(4096) PT* __physical pt[512];
} PDT;

typedef struct PDPT{
    _Alignas(4096) PDT* __physical pdt[512];
} PDPT;

typedef struct PML4T{
    _Alignas(4096) PDPT* __physical pdpt[512];
} PML4T;

typedef struct PML5T{
    _Alignas(4096) PML4T* __physical pml4t[512];
} PML5T;


void* get_mapped_virtual_address(void* __physical paddr);

void* __physical get_mapped_physical_addr(void* vaddr);

void* __physical read_cr3();

void* kmap(void* __physical paddr,void* vaddr_hint,size_t pcount);

int64_t get_linear_address_mask();

#endif //PHANTOMOS_MEMORY_H
