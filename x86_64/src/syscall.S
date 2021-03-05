

__handle_syscall:
    push %rbp
    mov %rsp,%rbp
    lea $__syscall_stack(%rip),%rsp 
    lea __syscalls(%rip),%r11
    lea (%r11,%rax,4),%rax 
    mov __syscalls_end(%rip),%r11
    cmp %rax,%r11

    __handle_syscall.exit:
    mov %rbp,%rsp
    pop %rbp
    xor %r11,%r11 
    sysret

