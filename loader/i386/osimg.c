//
// Created by chorm on 2020-07-21.
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
