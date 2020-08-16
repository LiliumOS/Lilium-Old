ENTRY(_start)

SECTIONS {
    . = 0x1000;

    .data.gdt ALIGN(4096):{
        KEEP(*(.data.gdt));
    }

    . = 0x20000;
    .text ALIGN(1024):{
        *(.text);
    }
    .text.init ALIGN(1024):{
        __text_init_start = .;
        KEEP(*(.text.init));
        __text_init_end = .;
    }
    .syscall ALIGN(1024):{
        KEEP(*(.syscall));
        __syscall_end = .;
    }
    .rodata ALIGN(1024):{
        *(.rodata);
    }
    .rodata.init ALIGN(1024):{
        __rodata_init_start = .;
        KEEP(*(.rodata.init));
        __rodata_init_end = .;
    }
    .data ALIGN(1024):{
        *(.data);
    }
    .data.init ALIGN(1024):{
        __data_init_start = .;
        KEEP(*(.data.init));
        __data_init_end = .;
    }
    .bss ALIGN(1024):{
        __bss_start = .;
        *(.bss)
        *(COMMON)
        __bss_end = .;
    }
    __vram_start = 0xb8000;
    .data.pt ALIGN(4096):{
        __pt_start = 0;
        __pml4t = 0;
        __pdpt = 0x1000;
        __pdt = 0x2000;
        __pt  = 0x3000;
    }

}