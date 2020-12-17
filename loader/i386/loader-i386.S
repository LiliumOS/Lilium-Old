
// ld/i386/loader-i386.S
// 
// This file is part of the PhantomOS loader.
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
//
// The PhantomOS loader is additionally Dual Licensed under the terms of the zlib
//  and the Apache v2 license, you may, at your option, copy and/or modify this file 
//  under the terms of those licenses, instead of the terms of the GNU General Public License.
//  See the PhantomOS Loader License header in the readme file, or the accompanying LICENSE-ZLIB and LICENSE-APACHE files.
// 

.set LONG_MODE, 536870912

.code32

.text

.global _start
.global _hlt

_start:
    # All of this is ix86 compatible.
    # Absolutely not r registers allowed
    lea __stack_head,%esp
    mov %esp,%ebp
    push %ebx
    # Testing for CPUID
    pushfl
    pop %eax
    mov %eax,%ecx
    xor $2097152,%eax
    push %eax
    popfl
    pushfl
    pop %eax
    push %ecx
    popfl
    xor %eax,%ecx
    jz _hlt # No CPUID, just halt
    mov $0x80000000,%eax
    cpuid
    cmp $0x80000001,%eax
    jb _hlt
    mov $0x80000001,%eax
    cpuid
    test $LONG_MODE,%edx
    jz _hlt
    mov %cr0,%eax
    and $0x7fffffff,%eax
    mov %eax,%cr0
    call load_osimg
_hlt:
    cli
    hlt
    jmp _hlt
