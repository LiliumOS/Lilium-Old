
.global outb
.global outw
.global outl
.global inb
.global inw
.global inl

outb:
    mov %di,%dx
    mov %sil,%al
    outb %al,%dx
    ret

outw:
    mov %di,%dx
    mov %si,%ax
    outw %ax,%dx
    ret

outl:
    mov %di,%dx
    mov %esi,%eax
    outl %eax,%dx
    ret

inb:
    mov %di,%dx
    inb %dx,%al
    ret

inw:
    mov %di,%dx
    inw %dx,%ax
    ret

inl:
    mov %di,%dx
    inl %dx,%eax
    ret