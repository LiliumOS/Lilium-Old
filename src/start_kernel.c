// memcpy.c
// 
// This file is part of PhantomOS.
//
// PhantomOS is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// PhantomOS is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with PhantomOS.  If not, see <https://www.gnu.org/licenses/>.
//
// PhantomOS is additionally distributed with a system call exemption
// As an exeption to the above license, 
//  proprietary software may interface with this software through the use of 
//  "system calls" to access any of the routines made available by the PhantomOS 
//  to programs written to be employed by the user.

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
