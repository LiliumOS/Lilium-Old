.set LONG_MODE, 536870912

.code32

.text

.global _start

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
    lea __pml4t,%edi
    mov %edi,%cr3
    xor %eax,%eax
    mov $4096,%ecx
    rep stosl
    mov %cr3,%edi
    lea __pdpt, %esi
    add $3,%esi
    mov %esi,(%edi)
    add $0x1000,%edi
    lea __pdt, %esi
    add $3,%esi
    mov %esi,(%edi)
    add $0x1000,%edi
    mov $0x03,%ebx
    mov $512,%ecx
    .SetEntry:
    mov %ebx, (%edi)
    add $0x1000,%ebx
    lea 8(%edi),%edi
    loop .SetEntry
    mov %cr4,%eax
    or $32,%eax
    mov %eax,%cr4
    mov $0xC0000080,%ecx
    rdmsr
    or $256,%eax
    wrmsr
    lgdt (__gdt_ptr)
    pop %edx
    jmp $__gdt_code, $start_x64
    _hlt:
    cli
    hlt
    jmp _hlt
