# acpi.S 
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


.global find_rdsp


find_rdsp:
    mov $0xE0000,%rax
    mov $0xFFFF0,%rdi
    .find:
    mov (%rax),%rcx
    movq $2329016660419433298,%r10
    cmpq %r10,%rcx
    je .exit
    lea 16(%rax),%rax
    cmp %rax,%rdi
    jae .find
    xor %rax, %rax
    .exit:
    ret
