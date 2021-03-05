/*
* ld/x86_64-pc-phantom-kernel.ld
* 
* This file is part of PhantomOS.
*
* PhantomOS is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* PhantomOS is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with PhantomOS.  If not, see <https://www.gnu.org/licenses/>.
*
* PhantomOS is additionally distributed with a system call exemption
* As an exeption to the above license, 
*  proprietary software may interface with this software through the use of 
*  "system calls" to access any of the routines made available by the PhantomOS 
*  to programs written to be employed by the user.
*/ 

ENTRY(_start)

PHDRS {
    gdt PT_LOAD;
    text PT_LOAD;
    data PT_LOAD;
    paging PT_LOAD;
}

SECTIONS {
    . = 0x1000;

    .data.gdt ALIGN(4096):{
        KEEP(*(.data.gdt));
    } :gdt

    . = 0x80000;
    
    .text.init ALIGN(1024):{
        __text_init_start = .;
        *(.text.init);
        __text_init_end = .;
        __text_start = .;
        *(.text);
        __text_end = .;
    } :text

    .rodata.init ALIGN(1024):{
        __rodata_init_start = .;
        *(.rodata.init);
        __rodata_init_end = .;
        __rodata_start = .;
        *(.rodata);
        __rodata_end = .;
        *(.rodata.str*);
    } :text
    
    .data.init ALIGN(4096):{
        __data_init_start = .;
        *(.data.init);
        __data_init_end = .;
        __data_start = .;
        *(.data);
        __data_end = .;
        __bss_start = .;
        *(.bss);
        *(COMMON);
        __bss_end = .;
        . = .;
        __syscall_stack = .;
        . = . + 4096;
    } :data

    .data.pt ALIGN(4096):{
        . = .;
        __pt_start = .;
        __pml4t = .;
        __pdpt = . + 0x1000;
        __pdt = . + 0x2000;
        __pt  = . + 0x3000;
        __pt_end = . + 0x10000;
    } :paging
    
    . = __pt_end;

    __vram_start = 0xb8000;
    __heap = 0xc0000;
}