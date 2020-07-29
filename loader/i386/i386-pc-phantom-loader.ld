ENTRY(_start)

PHDRS {
    text PT_LOAD;
    data PT_LOAD;
    img PT_LOAD;
}

SECTIONS {
    . = 0x10000;
    .mb ALIGN(1024):{
        LONG(0x1BADB002);
        LONG(3);
        LONG(-(0x1BADB002+3));
    } :text
    .text ALIGN(1024):{
        *(.text);
    }

    .bss.stack ALIGN(4096):{
        __stack_tail = .;
        . = .+4096;
        __stack_head = .;
    } :data
    . = .;
    .data.img ALIGN(1024): {
        KEEP(*(.data.img));
    } :img

}