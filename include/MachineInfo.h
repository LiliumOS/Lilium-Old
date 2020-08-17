//
// Created by chorm on 2020-08-17.
//

#ifndef PHANTOMOS_MACHINEINFO_H
#define PHANTOMOS_MACHINEINFO_H

#include <stdint.h>

uint32_t* cpuid(uint32_t idno,uint32_t* output,... /*uint32_t supplementary*/);

uint64_t rdmsr(uint32_t msr);
void wrmsr(uint32_t msr,uint64_t value);

///
/// Sets the given bits in control register 0
uint64_t set_cr0(uint64_t bits);

///
/// Clears the given bits in control register 0
uint64_t clear_cr0(uint64_t bits);

/// Gets the value of cr0
uint64_t get_cr0(void);

#endif //PHANTOMOS_MACHINEINFO_H
