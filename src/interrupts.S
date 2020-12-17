
# interrupts.S
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


.data

.global __interrupts
.global __interrupts_end

__interrupts:
.quad __interrupt_de
.quad __interrupt_db
.quad __interrupt_nmi
.quad __interrupt_bp
.quad __interrupt_of
.quad __interrupt_br
.quad __interrupt_ud
.quad __interrupt_nm
.quad __interrupt_df
.quad __interrupt_cso
.quad __interrupt_ts
.quad __interrupt_np
.quad __interrupt_ss
.quad __interrupt_gp
.quad __interrupt_pf
.quad 0
.quad __interrupt_mf
.quad __interrupt_ac
.quad __interrupt_mc
.quad __interrupt_xm
.quad __interrupt_ve
.space 72
.quad __interrupt_sx
.quad 0
__interrupts_end:

.text

.macro isr name, erc, number
.global __interrupt_\()\name

__interrupt_\()\name:
    .if (~\erc)&1
    sub $4,%rsp
    .endif
    push %rbp
    mov %rsp,%rbp
    and $~15,%rsp
    push %rax
    push %rbx
    push %rcx
    push %rdx
    push %rsi
    push %rdi
    push %r8
    push %r9
    push %r10
    push %r11
    push %r12
    push %r13
    push %r14
    push %r15
    mov %cr3,%rax
    push %rax
    push %rbp
    sub $512,%rsp
    fxsave (%rsp)
    mov %rsp,%rdi
    mov %rsp,%rcx
    mov $\number,%rsi
    xor %rdx,%rdx
    .if \erc
    mov 8(%rbp),%edx
    .endif
    call handle_interrupt
    mov %rsp,%rax
    fxrstor (%rsp)
    add $512,%rsp
    pop %rbp
    pop %r15
    pop %r14
    pop %r13
    pop %r12
    pop %r11
    pop %r10
    pop %r9
    pop %r8
    pop %rdi
    pop %rsi
    pop %rdx
    pop %rcx
    pop %rbx
    pop %rax
    leave
    add $4,%rsp
    iretq
.endm

isr de,0,0
isr db,0,1
isr nmi,0,2
isr bp,0,3
isr of,0,4
isr br,0,5
isr ud,0,6
isr nm,0,7
isr df,1,8
isr cso,0,9
isr ts,1,10
isr np,1,11
isr ss,1,12
isr gp,1,13
isr pf,1,14
isr mf,0,16
isr ac,1,17
isr mc,0,18
isr xm,0,19
isr ve,0,20
isr sx,1,30
