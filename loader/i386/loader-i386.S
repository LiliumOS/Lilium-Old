.set LONG_MODE, 536870912

.code32

.text

.global _start
.global _hlt

_start:
    # All of this is ix86 compatible.
    # Absolutely not r registers allowed
    lea __stack_head,%esp
    mov %esp,%ebp
    push %ebx
    # Testing for CPUID
    pushfl
    pop %eax
    mov %eax,%ecx
    xor $2097152,%eax
    push %eax
    popfl
    pushfl
    pop %eax
    push %ecx
    popfl
    xor %eax,%ecx
    jz _hlt # No CPUID, just halt
    mov $0x80000000,%eax
    cpuid
    cmp $0x80000001,%eax
    jb _hlt
    mov $0x80000001,%eax
    cpuid
    test $LONG_MODE,%edx
    jz _hlt
    mov %cr0,%eax
    and $0x7fffffff,%eax
    mov %eax,%cr0
    call load_osimg
_hlt:
    cli
    hlt
    jmp _hlt
