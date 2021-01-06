
# machein_info.S
# 
# This file is part of PhantomOS.

# PhantomOS is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.

# PhantomOS is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with PhantomOS.  If not, see <https://www.gnu.org/licenses/>.

# PhantomOS is additionally distributed with a system call exemption
# As an exeption to the above license, 
#  proprietary software may interface with this software through the use of 
#  "system calls" to access any of the routines made available by the PhantomOS 
#  to programs written to be employed by the user.


.global cpuid
.global rdmsr
.global wrmsr
.global set_cr0
.global clear_cr0
.global get_cr0
.global get_cr2
.global set_cr4_bits
.global clear_cr4
.global write_cr4
.global get_cr4
.global read_cr3

cpuid:
    mov %rbx,%r10
    mov %rdi,%rax
    mov %rdx,%rcx
    cpuid
    movl %eax,(%rsi)
    movl %ebx,4(%rsi)
    movl %edx,8(%rsi)
    movl %ecx,12(%rsi)
    mov %rdi,%rax
    mov %r10,%rbx
    ret

rdmsr:
    mov %edi,%ecx
    rdmsr
    shlq $32,%rdx
    or %rdx,%rax
    ret

wrmsr:
    mov %rsi,%rax
    shrq $32,%rsi
    mov %rsi,%rdx
    mov %rdi,%rcx
    wrmsr
    ret

set_cr0:
    mov %cr0,%rax
    or %rdi,%rax
    mov %rax,%cr0
    ret

clear_cr0:
    mov %cr0,%rax
    andnq %rdi,%rax,%rax
    mov %rax,%cr0
    ret

get_cr0:
    mov %cr0,%rax
    ret

get_cr2:
    mov %cr2,%rax
    ret

set_cr4_bits:
    mov %cr4,%rax
    or %rdi,%rax
    mov %rax,%cr4
    ret

clear_cr4:
    mov %cr4,%rax
    andn %rdi,%rax,%rax
    mov %rax,%cr4
    ret

get_cr4:
    mov %cr4,%rax
    ret

write_cr4:
    mov %rdi,%cr4
    ret

read_cr3:
    mov %cr3,%rax
    ret