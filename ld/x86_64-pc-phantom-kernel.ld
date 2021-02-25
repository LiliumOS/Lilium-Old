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
    higher_half_text PT_LOAD;
    higher_half_data PT_LOAD;
}

SECTIONS {
    . = 0x1000;

    .data.gdt ALIGN(4096):{
        KEEP(*(.data.gdt));
    } :gdt

    . = 0x80000;
    
    .text.init ALIGN(1024):{
        __text_init_start = .;
        KEEP(*(.text.init));
        __text_init_end = .;
    } :text

    .rodata.init ALIGN(1024):{
        __rodata_init_start = .;
        KEEP(*(.rodata.init));
        __rodata_init_end = .;
    } :text
    
    .data.init ALIGN(1024):{
        __data_init_start = .;
        KEEP(*(.data.init));
        __data_init_end = .;
    } :data
    .data.pt ALIGN(4096):{
        . = .;
        __pt_start = .;
        __pml4t = .;
        __pdpt = . + 0x1000;
        __pdt = . + 0x2000;
        __pt  = . + 0x3000;
    } : paging

    __vram_start = 0xb8000;
    . = 0x0000000000040000;
    /* . = 0xffff800000040000; */

    .text ALIGN(1024): AT(0x40000){
        *(.text);
        . = ALIGN(1024);
    } :higher_half_text

    .rodata ALIGN(1024): AT(0x40000+SIZEOF(.text)){
        __syscalls = .;
        KEEP(*(.syscall));
        __syscalls_end = .;
        *(.rodata);
    } :higher_half_text
    . = 0x0000000000440000;
    /* . = 0xffff800000440000; */
    .data ALIGN(1024): AT(0x440000){
        *(.data);
        __bss_start = .;
        *(.bss);
        *(COMMON);
        __bss_end = .;
        . = .;
        __syscall_stack = .;
        . = . + 4096;
    } :higher_half_data


}