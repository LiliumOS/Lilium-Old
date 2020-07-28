//
// Created by chorm on 2020-07-21.
//

#include <elf.h>
#include <memcpy.h>

union ElfHeader{
    unsigned e_ident[EI_NIDENT];
    Elf32_Ehdr head32;
    Elf64_Ehdr head64;
};

extern const union ElfHeader __head;

_Noreturn void _hlt(void);

void load_osimg(void){
    if(__head.e_ident[EI_MAG0]!=ELFMAG0
        ||__head.e_ident[EI_MAG1]!=ELFMAG1
        ||__head.e_ident[EI_MAG2]!=ELFMAG2
        ||__head.e_ident[EI_MAG3]!=ELFMAG3
        ||__head.e_ident[EI_DATA]!=ELFDATA2LSB
        ||__head.e_ident[EI_VERSION]!=EV_CURRENT)
        _hlt();
    else{
        if(__head.e_ident[EI_CLASS]==ELFCLASS64) {
            if(__head.head64.e_machine!=EM_X86_64)
                _hlt();
            Elf64_Addr entry = __head.head64.e_entry;
            if(entry>UINT32_MAX)
                _hlt();
            void(*_start)(void) = (void(*)(void))entry;
            Elf64_Off phead_off = __head.head64.e_phoff;
            if(phead_off>UINT32_MAX)
                _hlt();
            Elf64_Half phead_num = __head.head64.e_phnum;
            Elf64_Phdr* phead = ((unsigned char*)(&__head)+phead_off);
            for(Elf64_Phdr* chead = phead;chead!=phead+phead_num;chead++){
                if(chead->p_type!=PT_LOAD)
                    continue;
                Elf64_Addr laddr = chead->p_paddr;
                Elf64_Off loff = chead->p_offset;
                if(laddr>0x7f000000||laddr+chead->p_memsz>0x7f000000)
                    _hlt();
                memcpy((void *) laddr, ((unsigned char *) &__head) + loff, chead->p_filesz);
                if(chead->p_filesz<chead->p_memsz)
                    memset((void *) (laddr+chead->p_filesz),0,chead->p_memsz-chead->p_filesz);
            }
            _start();
        }
    }
}
