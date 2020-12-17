// ld/i386/i386-pc-phantom-loader.ld
// 
// This file is part of the PhantomOS loader.
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
//
// The PhantomOS loader is additionally Dual Licensed under the terms of the zlib
//  and the Apache v2 license, you may, at your option, copy and/or modify this file 
//  under the terms of those licenses, instead of the terms of the GNU General Public License.
//  See the PhantomOS Loader License header in the readme file, or the accompanying LICENSE-ZLIB and LICENSE-APACHE files.
// 

#include <elf.h>
#include <memcpy.h>

union ElfHeader{
    unsigned char e_ident[EI_NIDENT];
    Elf32_Ehdr head32;
    Elf64_Ehdr head64;
};

extern const union ElfHeader __head;

_Noreturn void _hlt(void);

void load_osimg(void){
    const union ElfHeader* head = &__head;
    if((head->e_ident[EI_MAG0]!=ELFMAG0)
        ||(head->e_ident[EI_MAG1]!=ELFMAG1)
        ||(head->e_ident[EI_MAG2]!=ELFMAG2)
        ||(head->e_ident[EI_MAG3]!=ELFMAG3)
        ||(head->e_ident[EI_DATA]!=ELFDATA2LSB)
        ||(head->e_ident[EI_VERSION]!=EV_CURRENT))
        _hlt();
    else{
        if(head->e_ident[EI_CLASS]==ELFCLASS64) {
            if(head->head64.e_machine!=EM_X86_64)
                _hlt();
            Elf64_Addr entry = head->head64.e_entry;
            if(entry>UINT32_MAX)
                _hlt();
            void(*_start)(void) = (void(*)(void))entry;
            Elf64_Off phead_off = head->head64.e_phoff;
            if(phead_off>UINT32_MAX)
                _hlt();
            Elf64_Half phead_num = head->head64.e_phnum;
            Elf64_Phdr* phead = (Elf64_Phdr *) ((unsigned char *) (&__head) + phead_off);
            for(Elf64_Phdr* chead = phead;chead!=phead+phead_num;chead++){
                if(chead->p_type!=PT_LOAD)
                    continue;
                Elf64_Addr laddr = chead->p_paddr;
                Elf64_Off loff = chead->p_offset;
                memcpy((void *) laddr, ((unsigned char *) &__head) + loff, chead->p_filesz);
                if(chead->p_filesz<chead->p_memsz)
                    memset((void *) (laddr+chead->p_filesz),0,chead->p_memsz-chead->p_filesz);
            }
            _start();
        }
    }
}
