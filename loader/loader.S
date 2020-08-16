

.section .data.gdt
__gdt:
__gdt_nul:
.short 0xFFFF
.short 0
.short 0
.byte 1
.byte 0
__gdt_code:
.short 0xFFFF
.short 0
.byte 0
.byte 0x9a
.byte 0xaf
.byte 0
__gdt_data:
.short 0xFFFF
.short 0
.byte 0
.byte 0x92
.byte 0x4f
.byte 0
__gdt_ptr:
.short __gdt_ptr-__gdt
.quad __gdt

.global _start
.global start_x64

.text

.code32
_start:
    cli
    mov %cr0,%eax
    and $0x7ffffff,%eax
    mov %eax,%cr0
    lea __pml4t,%edi
    xor %eax,%eax
    mov $4096,%ecx
    rep stosl
    lea __pml4t,%edi
    lea __pdpt, %esi
    add $3,%esi
    mov %esi,(%edi)
    lea __pdpt, %edi
    lea __pdt, %esi
    add $3,%esi
    mov %esi,(%edi)
    lea __pdt, %edi
    lea __pt, %esi
    add $3,%esi
    mov %esi,(%edi)
    lea __pt,%edi
    mov $0x03,%ebx
    mov $512,%ecx
    .SetEntry:
    mov %ebx, (%edi)
    add $0x1000,%ebx
    lea 8(%edi),%edi
    loop .SetEntry
    lea __pml4t,%edi
    mov %edi,%cr3
    mov %cr4,%eax
    or $32,%eax
    mov %eax,%cr4
    mov $0xC0000080,%ecx
    rdmsr
    or $256,%eax
    wrmsr
    mov %cr0,%eax
    or $0x80000000,%eax
    mov %eax,%cr0
    pop %edx
    lgdt __gdt_ptr
    jmp $__gdt_code, $start_x64

.code64

start_x64:
    # Now we can use x86_64 instructions
    xor %rdi,%rdi
    mov %ebx,%edi
    .start_kernel:
    call start_kernel
    _hlt:
    cli
    hlt
    jmp _hlt
