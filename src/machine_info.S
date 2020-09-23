
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