//
// Created by chorm on 2020-07-21.
//

#include <types.h>
#include <stdint.h>
#include <MachineInfo.h>

_Noreturn void _hlt(void);

void printk(const char* v);

void clear(void);

_Noreturn __attribute__((section(".text.init"))) void start_kernel(void* multiboot){
    (void)multiboot;
    clear();
    printk("Hello World\n");
    uint32_t buf[5] = {0};
    cpuid(0,buf);
    printk((const char*)&buf[1]);
    printk("\n");
    _hlt();
}

__attribute__((section(".text.init"))) void* handle_interrupt(interrupt_frame* v, uint64_t code,uint32_t errc,void* rsp){
    (void)errc;
    switch(code){
        case 9: // #DF, _hlt for now
            printk("Kernel received Double Fault\n");
            _hlt();
        case 13: // #GP
            printk("Kernel Received General Protection Exception\n");
        break;
        case 2:
            printk("Recieved Non-maskable Interrupt\n");
        default:
            ;
    }
    return rsp;
}