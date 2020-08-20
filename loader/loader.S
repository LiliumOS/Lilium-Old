

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
.short __gdt_ptr-__gdt-1
.quad __gdt

__idt:
.space 4096
__idt_ptr:
.short __idt_ptr-__idt-1
.quad __idt

.global _start
.global _hlt

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
    or $257,%eax
    wrmsr
    mov %cr0,%eax
    or $0x80000000,%eax
    mov %eax,%cr0
    call __init_idt
    lgdt __gdt_ptr
    lidt __idt_ptr
    sti
    pop %edx
    jmp $__gdt_code-__gdt, $start_x64


__init_idt:
    lea __interrupts_end,%edx
    lea __interrupts,%esi
    lea __idt,%edi
    .set_entry:
    movl (%esi),%eax
    je .set_entry
    movw (%esi),%ax
    movw %ax,(%edi)
    lea __gdt_code-__gdt,%eax
    movw %ax,2(%edi)
    movw $0x8E00,4(%edi)
    movw 2(%esi),%ax
    movw %ax,6(%edi)
    movl 4(%esi),%eax
    mov %eax,8(%edi)
    xor %eax,%eax
    movl %eax,12(%edi)
    lea 16(%edi),%edi
    lea 8(%esi),%esi
    cmp %esi,%edx
    jne .set_entry
    ret

.code64

start_x64:
    # Now we can use x86_64 instructions
    xor %rdi,%rdi
    mov %ebx,%edi
    and $~15,%rsp
    .start_kernel:
    call start_kernel
_hlt:
    cli
    hlt
    jmp _hlt


