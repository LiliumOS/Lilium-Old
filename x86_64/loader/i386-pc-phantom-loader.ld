/*
* loader/i386/i386-pc-phantom-loader.ld
* 
* This file is part of the PhantomOS loader.
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
*
* The PhantomOS loader is additionally Dual Licensed under the terms of the zlib
*  and the Apache v2 license, you may, at your option, copy and/or modify this file 
*  under the terms of those licenses, instead of the terms of the GNU General Public License.
*  See the PhantomOS Loader License header in the readme file, or the accompanying LICENSE-ZLIB and LICENSE-APACHE files.
*/ 


ENTRY(_start)

PHDRS {
    text PT_LOAD;
    data PT_LOAD;
    img PT_LOAD;
}

SECTIONS {
    . = 0x10000;
    .mb ALIGN(1024):{
        LONG(0x1BADB002);
        LONG(3);
        LONG(-(0x1BADB002+3));
    } :text
    .text ALIGN(1024):{
        *(.text);
    }

    .bss.stack ALIGN(4096):{
        __stack_tail = .;
        . = . + 4096;
        __stack_head = .;
    } :data
    . = .;
    .data.img ALIGN(1024): {
        KEEP(*(.data.img));
    } :img

}