
// acpi.h
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

#ifndef PHANTOMOS_ACPI_H_2020_08_25_20_13_22
#define PHANTOMOS_ACPI_H_2020_08_25_20_13_22

#include <stdint.h>

typedef struct{
    char sig[4];
    uint32_t size;
    uint8_t revision;
    uint8_t checksum;
    char OEMID[6];
    char OEMTableId[8];
    uint32_t creatorId;
    uint32_t creatorRev;
}__attribute((packed)) APICDSTHeader;

typedef struct{
    APICDSTHeader header;
    APICDSTHeader* sdtPtrs[];
}__attribute__((packed)) XSDT;

typedef struct{
    APICDSTHeader header;
    uint32_t sdtPtrs[];
}__attribute__((packed)) RSDT;

typedef struct{
    char sig[8];
    uint8_t checksum;
    char OEMID[6];
    uint8_t revision;
    uint32_t rdst_addr;
}__attribute__((packed)) RDSP;

typedef struct{
    RDSP rev1_struct;
    uint32_t length;
    XSDT* xdst_addr;
    uint8_t ext_checksum;
    uint8_t reserved[3];
}__attribute__((packed)) RDSP_v2;


RDSP* find_rdsp(void);



#endif
