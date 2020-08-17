
.global cpuid
.global rdmsr
.global wrmsr
.global set_cr0
.global clear_cr0
.global get_cr0

cpuid:
    mov %rdi,%rax
    mov %rdx,%rcx
    cpuid
    movl %eax,(%rsi)
    movl %ebx,4(%rsi)
    movl %ecx,8(%rsi)
    movl %edx,12(%rsi)
    mov %rdi,%rax
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
