
.global start_x64

.text

.code32
_start:
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
    pop %edx
    lgdt (__gdt_ptr)
    jmp $__gdt_code, $start_x64

.code64

start_x64:
    # Now we can use x86_64 instructions
    cli
    xor %rdi,%rdi
    mov %ebx,%edi
    .start_kernel:
    call start_kernel
    _hlt:
    cli
    hlt
    jmp _hlt