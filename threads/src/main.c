__attribute__((visibility("default"), used, section(".syscall"))) void (*syscalls[])(void) = {

};

__attribute__((visibility("default"), used)) long syscall_base = 0x100;