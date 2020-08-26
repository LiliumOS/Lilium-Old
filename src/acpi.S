
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
