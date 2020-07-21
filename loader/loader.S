
.global start_x64

.text

start_x64:
    # Now we can use x86_64 instructions
    cli
    xor %rdi,%rdi
    mov %ebx,%edi
    call start_kernel
    _hlt:
    cli
    hlt
    jmp _hlt