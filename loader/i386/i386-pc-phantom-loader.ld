ENTRY(_start)

PHDRS {
    text PT_LOAD;
    data PT_LOAD;
    img PT_LOAD AT(0x7f000000);
}

SECTIONS {
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

    .img 0x7f000000: {
        __head = .;
        KEEP(*(.img));
    } :img

}