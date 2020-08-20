
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
.quad 0
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
.space 80
.quad __interrupt_sx
.quad 0
__interrupts_end:

.text

.macro isr name, erc, number
.global __interrupt_\()\name

__interrupt_\()\name:
    push %rbp
    mov %rsp,%rbp
    and $~15,%rsp
    pushq $0
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
    mov %rbp,%rsi
    mov %cr3,%rax
    push %rax
    push %rbp
    sub $512,%rsp
    mov %rsp,%rcx
    mov $\number,%rdi
    xor %rdx,%rdx
    .if \erc
    mov 8(%rbp),%edx
    .endif
    call handle_interrupt
    mov %rsp,%rax
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
    .if \erc
    add $4,%rsp
    .endif
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
