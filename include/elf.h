// elf.h
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

#ifndef LCNIX_ELF_H
#define LCNIX_ELF_H

#include <stdint.h>

typedef uint32_t Elf32_Addr;
typedef uint64_t Elf64_Addr;
typedef uint16_t Elf32_Section;
typedef uint16_t Elf64_Section;
typedef uint32_t Elf32_Off;
typedef uint64_t Elf64_Off;
typedef uint16_t Elf32_Versym;
typedef uint16_t Elf64_Versym;
typedef unsigned char Elf_Byte;
typedef uint16_t Elf32_Half;
typedef uint16_t Elf64_Half;
typedef int32_t Elf32_Sword;
typedef uint32_t Elf32_Word;
typedef int32_t Elf64_Sword;
typedef uint32_t Elf64_Word;
typedef int64_t Elf32_Sxword;
typedef uint64_t Elf32_Xword;
typedef int64_t Elf64_Sxword;
typedef uint64_t Elf64_Xword;

#define EI_MAG0 0
#define EI_MAG1 1
#define EI_MAG2 2
#define EI_MAG3 3

#define ELFMAG0 0x7f
#define ELFMAG1 'E'
#define ELFMAG2 'L'
#define ELFMAG3 'F'

#define EI_CLASS 4

#define ELFCLASSNONE 0
#define ELFCLASS32 1
#define ELFCLASS64 2

#define EI_DATA 5

#define ELFDATANONE 0
#define ELFDATA2LSB 1
#define ELFDATA2MSB 2

#define EI_VERSION 6

#define EV_NONE 0
#define EV_CURRENT 1

#define EI_OSABI 7

#define EI_ABIVERSION 8

#define EI_PAD 9
#define EI_NIDENT 16

typedef struct Elf32_Ehdr
{
    Elf_Byte e_ident[EI_NIDENT];
    Elf32_Half e_type;
    Elf32_Half e_machine;
    Elf32_Word e_version;
    Elf32_Addr e_entry;
    Elf32_Off e_phoff;
    Elf32_Off e_shoff;
    Elf32_Word e_flags;
    Elf32_Half e_ehsize;
    Elf32_Half e_phentsize;
    Elf32_Half e_phnum;
    Elf32_Half e_shentsize;
    Elf32_Half e_shnum;
    Elf32_Section e_shstrndx;
} Elf32_Ehdr;

typedef struct Elf64_Ehdr
{
    Elf_Byte e_ident[EI_NIDENT];
    Elf64_Half e_type;
    Elf64_Half e_machine;
    Elf64_Word e_version;
    Elf64_Addr e_entry;
    Elf64_Off e_phoff;
    Elf64_Off e_shoff;
    Elf64_Word e_flags;
    Elf64_Half e_ehsize;
    Elf64_Half e_phentsize;
    Elf64_Half e_phnum;
    Elf64_Half e_shentsize;
    Elf64_Half e_shnum;
    Elf32_Section e_shstrndx;
} Elf64_Ehdr;

typedef struct
{
    Elf32_Word p_type;
    Elf32_Off p_offset;
    Elf32_Addr p_vaddr;
    Elf32_Addr p_paddr;
    Elf32_Word p_filesz;
    Elf32_Word p_memsz;
    Elf32_Word p_flags;
    Elf32_Word p_align;
} Elf32_Phdr;

#define ET_NONE 0
#define ET_REL 1
#define ET_EXEC 2
#define ET_DYN 3
#define ET_CORE 4
#define ET_LOPROC 0xff00
#define ET_HIPROC 0xffff

///
// EM value list taken from the llvm-project (llvm/include/BinaryFormat/ELF.h)

//
//EM_NONE = 0,           // No machine
#define EM_NONE 0
//EM_M32 = 1,            // AT&T WE 32100
#define EM_M32 1
//EM_SPARC = 2,          // SPARC
#define EM_SPARC 2
//EM_386 = 3,            // Intel 386
#define EM386 3
//EM_68K = 4,            // Motorola 68000
#define EM68K 4
//EM_88K = 5,            // Motorola 88000
#define EM88K 5
//EM_IAMCU = 6,          // Intel MCU
#define EM_IAMCU
//EM_860 = 7,            // Intel 80860
#define EM_860 7
//EM_MIPS = 8,           // MIPS R3000
#define EM_MIPS 8
//EM_S370 = 9,           // IBM System/370
#define EM_S370 9
//EM_MIPS_RS3_LE = 10,   // MIPS RS3000 Little-endian
#define EM_MIPS_RS3_LE 10
//EM_PARISC = 15,        // Hewlett-Packard PA-RISC
#define EM_PARISC 15
//EM_VPP500 = 17,        // Fujitsu VPP500
#define EM_VPP500 17
//EM_SPARC32PLUS = 18,   // Enhanced instruction set SPARC
#define EM_SPARC32PLUS 18
//EM_960 = 19,           // Intel 80960
#define EM_960 19
//EM_PPC = 20,           // PowerPC
#define EM_PPC 20
//EM_PPC64 = 21,         // PowerPC64
#define EM_PPC64 21
//EM_S390 = 22,          // IBM System/390
#define EM_S390 22
//EM_SPU = 23,           // IBM SPU/SPC
#define EM_SPU 23
//EM_V800 = 36,          // NEC V800
#define EM_V800
//EM_FR20 = 37,          // Fujitsu FR20
#define EM_FR20 37
//EM_RH32 = 38,          // TRW RH-32
#define EM_RH32
//EM_RCE = 39,           // Motorola RCE
#define EM_RCE 39
//EM_ARM = 40,           // ARM
#define EM_ARM 40
//EM_ALPHA = 41,         // DEC Alpha
#define EM_ALPHA 41
//EM_SH = 42,            // Hitachi SH
#define EM_SH 42
//EM_SPARCV9 = 43,       // SPARC V9
#define EM_SPARCV9
//EM_TRICORE = 44,       // Siemens TriCore
#define EM_TRICORE 44
//EM_ARC = 45,           // Argonaut RISC Core
#define EM_ARC 45
//EM_H8_300 = 46,        // Hitachi H8/300
#define EM_H8_300 46
//EM_H8_300H = 47,       // Hitachi H8/300H
#define EM_H8_300H 47
//EM_H8S = 48,           // Hitachi H8S
#define EM_H8S 48
//EM_H8_500 = 49,        // Hitachi H8/500
#define EM_H8_500 49
//EM_IA_64 = 50,         // Intel IA-64 processor architecture
#define EM_IA_64 50
//EM_MIPS_X = 51,        // Stanford MIPS-X
#define EM_MIPS_X 51
//EM_COLDFIRE = 52,      // Motorola ColdFire
#define EM_COLDFIRE 52
//EM_68HC12 = 53,        // Motorola M68HC12
#define EM_68HC12 53
//EM_MMA = 54,           // Fujitsu MMA Multimedia Accelerator
#define EM_MMA 54
//EM_PCP = 55,           // Siemens PCP
#define EM_PCP 55
//EM_NCPU = 56,          // Sony nCPU embedded RISC processor
#define EM_NCPU 56
//EM_NDR1 = 57,          // Denso NDR1 microprocessor
#define EM_NDR1 57
//EM_STARCORE = 58,      // Motorola Star*Core processor
#define EM_STARCORE 58
//EM_ME16 = 59,          // Toyota ME16 processor
#define EM_ME16 59
//EM_ST100 = 60,         // STMicroelectronics ST100 processor
#define EM_ST100 60
//EM_TINYJ = 61,         // Advanced Logic Corp. TinyJ embedded processor family
#define EM_TINYJ 61
//EM_X86_64 = 62,        // AMD x86-64 architecture
#define EM_X86_64 62
//EM_PDSP = 63,          // Sony DSP Processor
#define EM_PDSP 63
//EM_PDP10 = 64,         // Digital Equipment Corp. PDP-10
#define EM_PDP10 64
//EM_PDP11 = 65,         // Digital Equipment Corp. PDP-11
#define EM_PDP11 65
//EM_FX66 = 66,          // Siemens FX66 microcontroller
#define EM_FX66 66
//EM_ST9PLUS = 67,       // STMicroelectronics ST9+ 8/16 bit microcontroller
#define EM_ST9PLUS 67
//EM_ST7 = 68,           // STMicroelectronics ST7 8-bit microcontroller
#define EM_ST7 68
//EM_68HC16 = 69,        // Motorola MC68HC16 Microcontroller
#define EM_68HC16 69
//EM_68HC11 = 70,        // Motorola MC68HC11 Microcontroller
#define EM_68HC11 70
//EM_68HC08 = 71,        // Motorola MC68HC08 Microcontroller
#define EM_68HC08 71
//EM_68HC05 = 72,        // Motorola MC68HC05 Microcontroller
#define EM_68HC05 72
//EM_SVX = 73,           // Silicon Graphics SVx
#define EM_SVX 73
//EM_ST19 = 74,          // STMicroelectronics ST19 8-bit microcontroller
#define EM_ST19 74
//EM_VAX = 75,           // Digital VAX
#define EM_VAX 75
//EM_CRIS = 76,          // Axis Communications 32-bit embedded processor
#define EM_CRIS 76
//EM_JAVELIN = 77,       // Infineon Technologies 32-bit embedded processor
#define EM_JAVELIN 77
//EM_FIREPATH = 78,      // Element 14 64-bit DSP Processor
#define EM_FIREPATH 78
//EM_ZSP = 79,           // LSI Logic 16-bit DSP Processor
#define EM_ZSP 79
//EM_MMIX = 80,          // Donald Knuth's educational 64-bit processor
#define EM_MMIX 80
//EM_HUANY = 81,         // Harvard University machine-independent object files
#define EM_HUANY 81
//EM_PRISM = 82,         // SiTera Prism
#define EM_PRISM 82
//EM_AVR = 83,           // Atmel AVR 8-bit microcontroller
#define EM_AVR 83
//EM_FR30 = 84,          // Fujitsu FR30
#define EM_FR30 84
//EM_D10V = 85,          // Mitsubishi D10V
#define EM_D10V 85
//EM_D30V = 86,          // Mitsubishi D30V
#define EM_D30V 86
//EM_V850 = 87,          // NEC v850
#define EM_V850 87
//EM_M32R = 88,          // Mitsubishi M32R
#define EM_M32R 88
//EM_MN10300 = 89,       // Matsushita MN10300
#define EM_MN10300 89
//EM_MN10200 = 90,       // Matsushita MN10200
#define EM_MN10200 90
//EM_PJ = 91,            // picoJava
#define EM_PJ 91
//EM_OPENRISC = 92,      // OpenRISC 32-bit embedded processor
#define EM_OPENRISC 92
//EM_ARC_COMPACT = 93,   // ARC International ARCompact processor (old
#define EM_ARC_COMPACT 93
//EM_XTENSA = 94,        // Tensilica Xtensa Architecture
#define EM_XTENSA 94
//EM_VIDEOCORE = 95,     // Alphamosaic VideoCore processor
#define EM_VIDEOCORE 95
//EM_TMM_GPP = 96,       // Thompson Multimedia General Purpose Processor
#define EM_TMM_GPP 96
//EM_NS32K = 97,         // National Semiconductor 32000 series
#define EM_NS32K 97
//EM_TPC = 98,           // Tenor Network TPC processor
#define EM_TPC 98
//EM_SNP1K = 99,         // Trebia SNP 1000 processor
#define EM_SNP1K 99
//EM_ST200 = 100,        // STMicroelectronics (www.st.com) ST200
#define EM_ST200 100
//EM_IP2K = 101,         // Ubicom IP2xxx microcontroller family
#define EM_IP2K 101
//EM_MAX = 102,          // MAX Processor
#define EM_MAX 102
//EM_CR = 103,           // National Semiconductor CompactRISC microprocessor
#define EM_CR 103
//EM_F2MC16 = 104,       // Fujitsu F2MC16
#define EM_F2MC16 104
//EM_MSP430 = 105,       // Texas Instruments embedded microcontroller msp430
#define EM_MSP430 105
//EM_BLACKFIN = 106,     // Analog Devices Blackfin (DSP) processor
#define EM_BLACKFIN 106
//EM_SE_C33 = 107,       // S1C33 Family of Seiko Epson processors
#define EM_SE_C33 107
//EM_SEP = 108,          // Sharp embedded microprocessor
#define EM_SEP 108
//EM_ARCA = 109,         // Arca RISC Microprocessor
#define EM_ARCA 109
//EM_UNICORE = 110,      // Microprocessor series from PKU-Unity Ltd. and MPRC
//// of Peking University
#define EM_UNICORE 110
//EM_EXCESS = 111,       // eXcess: 16/32/64-bit configurable embedded CPU
#define EM_EXCESS 111
//EM_DXP = 112,          // Icera Semiconductor Inc. Deep Execution Processor
#define EM_DXP 112
//EM_ALTERA_NIOS2 = 113, // Altera Nios II soft-core processor
#define EM_ALTERA_NIOS2 113
//EM_CRX = 114,          // National Semiconductor CompactRISC CRX
#define EM_CRX 114
//EM_XGATE = 115,        // Motorola XGATE embedded processor
#define EM_XGATE 115
//EM_C166 = 116,         // Infineon C16x/XC16x processor
#define EM_C166 116
//EM_M16C = 117,         // Renesas M16C series microprocessors
#define EM_M16C 117
//EM_DSPIC30F = 118,     // Microchip Technology dsPIC30F Digital Signal
//// Controller
#define EM_DSPIC30F 118
//EM_CE = 119,           // Freescale Communication Engine RISC core
#define EM_CE 119
//EM_M32C = 120,         // Renesas M32C series microprocessors
#define EM_M32C 120
//EM_TSK3000 = 131,      // Altium TSK3000 core
#define EM_TSK3000 131
//EM_RS08 = 132,         // Freescale RS08 embedded processor
#define EM_RS08 132
//EM_SHARC = 133,        // Analog Devices SHARC family of 32-bit DSP
//// processors
#define EM_SHARC 133
//EM_ECOG2 = 134,        // Cyan Technology eCOG2 microprocessor
#define EM_ECOG 134
//EM_SCORE7 = 135,       // Sunplus S+core7 RISC processor
#define EM_SCORE7 135
//EM_DSP24 = 136,        // New Japan Radio (NJR) 24-bit DSP Processor
#define EM_DSP24 136
//EM_VIDEOCORE3 = 137,   // Broadcom VideoCore III processor
#define EM_VIDEOCORE3 137
//EM_LATTICEMICO32 = 138, // RISC processor for Lattice FPGA architecture
#define EM_LATTICEMICO32 138
//EM_SE_C17 = 139,        // Seiko Epson C17 family
#define EM_SE_C17 139
//EM_TI_C6000 = 140,      // The Texas Instruments TMS320C6000 DSP family
#define EM_TI_C600 140
//EM_TI_C2000 = 141,      // The Texas Instruments TMS320C2000 DSP family
#define EM_TI_C2000 141
//EM_TI_C5500 = 142,      // The Texas Instruments TMS320C55x DSP family
#define EM_TI_C5500 142
//EM_MMDSP_PLUS = 160,    // STMicroelectronics 64bit VLIW Data Signal Processor
#define EM_MMDSP_PLUS 160
//EM_CYPRESS_M8C = 161,   // Cypress M8C microprocessor
#define EM_CYPRESS_M8C 161
//EM_R32C = 162,          // Renesas R32C series microprocessors
#define EM_R32C 162
//EM_TRIMEDIA = 163,      // NXP Semiconductors TriMedia architecture family
#define EM_TRIMEDIA 163
//EM_HEXAGON = 164,       // Qualcomm Hexagon processor
#define EM_HEXAGON 164
//EM_8051 = 165,          // Intel 8051 and variants
#define EM_8051 165
//EM_STXP7X = 166,        // STMicroelectronics STxP7x family of configurable
//// and extensible RISC processors
#define EM_STXP7X 166
//EM_NDS32 = 167,         // Andes Technology compact code size embedded RISC
//// processor family
#define EM_NDS32 167
//EM_ECOG1 = 168,         // Cyan Technology eCOG1X family
#define EM_ECOG1 168
//EM_ECOG1X = 168,        // Cyan Technology eCOG1X family
#define EM_ECOG1X 168
//EM_MAXQ30 = 169,        // Dallas Semiconductor MAXQ30 Core Micro-controllers
#define EM_MAXQ30 169
//EM_XIMO16 = 170,        // New Japan Radio (NJR) 16-bit DSP Processor
#define EM_XIM016 170
//EM_MANIK = 171,         // M2000 Reconfigurable RISC Microprocessor
#define EM_MANIK 171
//EM_CRAYNV2 = 172,       // Cray Inc. NV2 vector architecture
#define EM_CRAYNV2 172
//EM_RX = 173,            // Renesas RX family
#define EM_RX 173
//EM_METAG = 174,         // Imagination Technologies META processor
//// architecture
#define EM_METAG 174
//EM_MCST_ELBRUS = 175,   // MCST Elbrus general purpose hardware architecture
#define EM_MCST_ELBRUS 175
//EM_ECOG16 = 176,        // Cyan Technology eCOG16 family
#define EM_ECOG16
//EM_CR16 = 177,          // National Semiconductor CompactRISC CR16 16-bit
//// microprocessor
#define EM_CR16 177
//EM_ETPU = 178,          // Freescale Extended Time Processing Unit
#define EM_ETPU 178
//EM_SLE9X = 179,         // Infineon Technologies SLE9X core
#define EM_SLE9X 179
//EM_L10M = 180,          // Intel L10M
#define EM_L10M 180
//EM_K10M = 181,          // Intel K10M
#define EM_K10M 181
//EM_AARCH64 = 183,       // ARM AArch64
#define EM_AARCH64 183
//EM_AVR32 = 185,         // Atmel Corporation 32-bit microprocessor family
#define EM_AVR32 185
//EM_STM8 = 186,          // STMicroeletronics STM8 8-bit microcontroller
#define EM_STM8 186
//EM_TILE64 = 187,        // Tilera TILE64 multicore architecture family
#define EM_TILE64 187
//EM_TILEPRO = 188,       // Tilera TILEPro multicore architecture family
#define EM_TILEPRO 188
//EM_CUDA = 190,          // NVIDIA CUDA architecture
#define EM_CUDA 190
//EM_TILEGX = 191,        // Tilera TILE-Gx multicore architecture family
#define EM_TILEGX 191
//EM_CLOUDSHIELD = 192,   // CloudShield architecture family
#define EM_CLOUDSHIELD 192
//EM_COREA_1ST = 193,     // KIPO-KAIST Core-A 1st generation processor family
#define EM_COREA_1ST 193
//EM_COREA_2ND = 194,     // KIPO-KAIST Core-A 2nd generation processor family
#define EM_COREA_2ND 194
//EM_ARC_COMPACT2 = 195,  // Synopsys ARCompact V2
#define EM_COMPACT2 195
//EM_OPEN8 = 196,         // Open8 8-bit RISC soft processor core
#define EM_OPEN8 196
//EM_RL78 = 197,          // Renesas RL78 family
#define EM_RL78 197
//EM_VIDEOCORE5 = 198,    // Broadcom VideoCore V processor
#define EM_VIDEO_CORE5 198
//EM_78KOR = 199,         // Renesas 78KOR family
#define EM_78KOR 199
//EM_56800EX = 200,       // Freescale 56800EX Digital Signal Controller (DSC)
#define EM_56800EX 200
//EM_BA1 = 201,           // Beyond BA1 CPU architecture
#define EM_BA1 201
//EM_BA2 = 202,           // Beyond BA2 CPU architecture
#define EM_BA2 202
//EM_XCORE = 203,         // XMOS xCORE processor family
#define EM_XCORE 203
//EM_MCHP_PIC = 204,      // Microchip 8-bit PIC(r) family
#define EM_MCHP_PIC 204
//EM_INTEL205 = 205,      // Reserved by Intel
//EM_INTEL206 = 206,      // Reserved by Intel
//EM_INTEL207 = 207,      // Reserved by Intel
//EM_INTEL208 = 208,      // Reserved by Intel
//EM_INTEL209 = 209,      // Reserved by Intel
//EM_KM32 = 210,          // KM211 KM32 32-bit processor
#define EM_KM32 210
//EM_KMX32 = 211,         // KM211 KMX32 32-bit processor
#define EM_KMX32 211
//EM_KMX16 = 212,         // KM211 KMX16 16-bit processor
#define EM_KMX16 212
//EM_KMX8 = 213,          // KM211 KMX8 8-bit processor
#define EM_KMX8 213
//EM_KVARC = 214,         // KM211 KVARC processor
#define EM_KVARC 214
//EM_CDP = 215,           // Paneve CDP architecture family
#define EM_CDP 215
//EM_COGE = 216,          // Cognitive Smart Memory Processor
#define EM_COGE 216
//EM_COOL = 217,          // iCelero CoolEngine
#define EM_COOL 217
//EM_NORC = 218,          // Nanoradio Optimized RISC
#define EM_NORC 218
//EM_CSR_KALIMBA = 219,   // CSR Kalimba architecture family
#define EM_CSR_KALIMBA 219
//EM_AMDGPU = 224,        // AMD GPU architecture
#define EM_AMDGPU 224
//EM_RISCV = 243,         // RISC-V
#define EM_RISCV 243
//EM_LANAI = 244,         // Lanai 32-bit processor
#define EM_LANAI 244
//EM_BPF = 247,           // Linux kernel bpf virtual machine
#define EM_BPF 247
//EM_VE = 251,            // NEC SX-Aurora VE
#define EM_VE 251

#define EM_65816 257 // WDC 65816

typedef struct
{
    Elf64_Word p_type;
    Elf64_Word p_flags;
    Elf64_Off p_offset;
    Elf64_Addr p_vaddr;
    Elf64_Addr p_paddr;
    Elf64_Xword p_filesz;
    Elf64_Xword p_memsz;
    Elf64_Xword p_align;
} Elf64_Phdr;

#define PT_NULL (0)
#define PT_LOAD (1)
#define PT_DYNAMIC (2)
#define PT_INTERP (3)
#define PT_NOTE (4)
#define PT_SHLIB (5)
#define PT_PHDR (6)
#define PT_LOOS (0x60000000)
#define PT_HIOS (0x6fffffff)
#define PT_LOPROC (0x70000000)
#define PT_HIPROC (0x7fffffff)

typedef struct
{
    Elf32_Word sh_name;
    Elf32_Word sh_type;
    Elf32_Word sh_flags;
    Elf32_Addr sh_addr;
    Elf32_Off sh_offset;
    Elf32_Word sh_size;
    Elf32_Word sh_link;
    Elf32_Word sh_info;
    Elf32_Word sh_addralign;
    Elf32_Word sh_entsize;
} Elf32_Shdr;

typedef struct
{
    Elf64_Word sh_name;
    Elf64_Word sh_type;
    Elf64_Word sh_flags;
    Elf64_Addr sh_addr;
    Elf64_Off sh_offset;
    Elf64_Xword sh_size;
    Elf64_Word sh_link;
    Elf64_Word sh_info;
    Elf64_Xword sh_addralign;
    Elf64_Xword sh_entsize;
} Elf64_Shdr;

#define SHN_UNDEF (0x00)

#define SHT_NULL (0)
#define SHT_PROGBITS (1)
#define SHT_SYMTAB (2)
#define SHT_STRTAB (3)
#define SHT_RELA (4)
#define SHT_HASH (5)
#define SHT_DYNAMIC (6)
#define SHT_NOTE (7)
#define SHT_NOBITS (8)
#define SHT_REL (9)
#define SHT_SHLIB (10)
#define SHT_DYNSYM (11)
#define SHT_LOOS (0x60000000)
#define SHT_HIOS (0x6fffffff)
#define SHT_LOPROC (0x70000000)
#define SHT_HIPROC (0x7fffffff)
#define SHT_LOUSER (0x80000000)
#define SHT_HIUSER (0xffffffff)

typedef struct
{
    Elf32_Word st_name;
    Elf32_Addr st_value;
    Elf32_Word st_size;
    Elf_Byte st_info;
    Elf_Byte st_other;
    Elf32_Section st_shndx;
} Elf32_Sym;

typedef struct
{
    Elf64_Word st_name;
    Elf_Byte st_info;
    Elf_Byte st_other;
    Elf64_Section st_shndx;
    Elf64_Addr st_value;
    Elf64_Xword st_size;
} Elf64_Sym;

#define STB_LOCAL (0)
#define STB_GLOBAL (1)
#define STB_WEAK (2)

#define STT_NOTYPE (0)
#define STT_OBJECT (1)
#define STT_FUNC (2)

#define ELF32_R_SYM(INFO) ((INFO) >> 8)
#define ELF32_R_TYPE(INFO) ((uint8_t)(INFO))

typedef struct
{
    Elf32_Addr r_offset;
    Elf32_Word r_info;
} Elf32_Rel;

typedef struct
{
    Elf64_Addr r_offset;
    Elf64_Xword r_info;
} Elf64_Rel;

typedef struct
{
    Elf32_Addr r_offset;
    Elf32_Word r_info;
    Elf32_Sword r_addend;
} Elf32_Rela;

typedef struct
{
    Elf64_Addr r_offset;
    Elf64_Xword r_info;
    Elf64_Sxword r_addend;
} Elf64_Rela;

typedef struct
{
    Elf32_Sword d_tag;
    union
    {
        Elf32_Word d_val;
        Elf32_Addr d_ptr;
    } d_un;
} Elf32_Dyn;

typedef struct
{
    Elf64_Sxword d_tag;
    union
    {
        Elf64_Xword d_val;
        Elf64_Addr d_ptr;
    } d_un;
} Elf64_Dyn;

#endif //LCNIX_ELF_H
