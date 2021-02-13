PHDRS{
    headers PT_PHDR PHDRS;
    text PT_LOAD FILEHDR PHDRS;
    data PT_LOAD;
    dynamic PT_DYNAMIC;
}

SECTIONS{
    . = SIZEOF_HEADERS;
    .text : { 
        *(.text);
    } :text
    .rodata : {
        *(.rodata);
        __syscall_begin = 0;
        *(.syscall);
        __syscall_end = 0;
    }

    . = . + ALIGN(0x1000);
    .data : {
        *(.data);
    } :data 
    .dynamic : {
        *(.dynamic);
    } :data :dynamic 
    .bss : {
        *(.bss);
        *(COMMON);
    } :data
}