//
// Created by chorm on 2020-07-21.
//

#include <types.h>
#include <acpi.h>
#include <stdint.h>
#include <MachineInfo.h>
#include <stdlib.h>

_Noreturn void _hlt(void);

void printk(const char* v);

void clear(void);

_Noreturn __attribute__((section(".text.init"))) void start_kernel(void* multiboot){
    (void)multiboot;
    clear();
    printk("Hello World\n");
    uint32_t buf[5] = {0};
    cpuid(0,buf);
    char ticker[2] = {'0',0};
    for(int i = 0; i < 24; i++) {
        printk((const char*)&buf[1]);
        printk(ticker);
        ticker[0]++;
        printk("\n");
    }

    RDSP* rdsp = find_rdsp();
    RDSP_v2* rdspv2 = NULL;
    APICDSTHeader* rsdt_or_xsdt;
    if(rdsp) {
        unsigned char chksm = 0;
        for(unsigned char* sum_ptr = (unsigned char*)rdsp;sum_ptr!=(unsigned char*)(rdsp+1);sum_ptr++)
            chksm += *sum_ptr;
        if(chksm){
            printk("RDSP Checksum failure");
            _hlt();
        }
        if(rdsp->revision>=2){
            rdspv2 = (RDSP_v2*)rdsp;
            for(unsigned char* sum_ptr = (unsigned char*)rdspv2;sum_ptr!=(unsigned char*)(rdspv2+1);sum_ptr++)
                chksm += *sum_ptr;
            if(chksm){
                printk("RDSPv2 Checksum failure");
                _hlt();
            }
            rsdt_or_xsdt = (APICDSTHeader *) rdspv2->xdst_addr;
        }else{
            rsdt_or_xsdt = (APICDSTHeader *)(unsigned long long)rdsp->rdst_addr;
        }

    }



    _hlt();
}

__attribute__((section(".text.init"))) void* handle_interrupt(interrupt_frame* v, uint64_t code,uint32_t errc,void* rsp){
    (void)errc;
    switch(code){
        case 8: // #DF, _hlt for now
            clear();
            printk("Kernel received Double Fault\n");
            _hlt();
        case 14: // #PF
            printk("Kernel Received Page Fault\n");
        break;
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
