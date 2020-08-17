//
// Created by chorm on 2020-07-21.
//

#include <stdint.h>

_Noreturn void _hlt(void);

void printk(const char* v);

_Noreturn __attribute__((section(".text.init"))) void start_kernel(void* multiboot){
    (void)multiboot;
    printk("Hello World");
    _hlt();
}

__attribute__((section(".text.init"))) void handle_interrupt(void* v, uint64_t code,uint32_t errc){
    switch(code){
        case 9: // DF, _hlt for now
            _hlt();
        default:
            ;
    }
}