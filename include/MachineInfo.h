//
// Created by chorm on 2020-08-17.
//

#ifndef PHANTOMOS_MACHINEINFO_H
#define PHANTOMOS_MACHINEINFO_H

#include <stdint.h>

/**
 * Gets the cpuid and stores it into `output`
 * @param idno the cpuid value to pass.
 * @param output The output registers, in order %eax,%ebx,%edx,%ecx
 * @param ... Some cpuid operations have a supplementary code in %ecx.
 * @return A pointer to the output
 */
uint32_t* cpuid(uint32_t idno,uint32_t* output,... /*uint32_t supplementary*/);

uint64_t rdmsr(uint32_t msr);
void wrmsr(uint32_t msr,uint64_t value);

enum CR0{
    PE = 1,
    MP = 2,
    EM = 4,
    TS = 8,
    ET = 16,
    NE = 32,
    WP = (1<<16),
    AM = (1<<18),
    NW = (1<<29),
    CD = (1<<30),
    PG = (1<<31)
};

///
/// Sets the given bits in control register 0
uint64_t set_cr0(uint64_t bits);

///
/// Clears the given bits in control register 0
uint64_t clear_cr0(uint64_t bits);

/// Gets the value of cr0
uint64_t get_cr0(void);

void* get_cr2(void);

enum CR4{
    VME = 1,
    PVI = 2,
    TSD = 4,
    DE  = 8,
    PSE = 16,
    PAE = 32,
    MCE = 64,
    PGE = 128,
    PCE = 256,
    OSFXSR = 512,
    OSXMMEXCEPT = 1024,
    UMIP = 2048,
    VMXE = 8192,
    SMXE = 16384,
    PCIDE = (1<<17),
    OSXSAVE = (1<<18),
    SMEP = (1<<20),
    SMAP = (1<<21)
};

uint64_t set_cr4_bits(uint64_t bits);
uint64_t clear_cr4(uint64_t bits);
void write_cr4(uint64_t value);
uint64_t get_cr4(void);

#endif //PHANTOMOS_MACHINEINFO_H
