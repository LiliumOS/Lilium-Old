//
// Created by chorm on 2020-08-17.
//

#ifndef PHANTOMOS_TYPES_H
#define PHANTOMOS_TYPES_H

#include <stdint.h>

typedef struct interrupt_frame{
    unsigned char fxinfo[512];
    void* rbp; // Frame Base Address
    void* cr3; // Page Table Base Address
    uint64_t r15;
    uint64_t r14;
    uint64_t r13;
    uint64_t r12;
    uint64_t r11;
    uint64_t r10;
    uint64_t r9;
    uint64_t r8;
    uint64_t rdi;
    uint64_t rsi;
    uint64_t rdx;
    uint64_t rcx;
    uint64_t rbx;
    uint64_t rax;
}__attribute__((aligned(16))) interrupt_frame;


#endif //PHANTOMOS_TYPES_H
