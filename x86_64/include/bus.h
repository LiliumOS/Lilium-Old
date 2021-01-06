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

#ifndef PHANTOMOS_BUS_H
#define PHANTOMOS_BUS_H

#include <stdint.h>

void outb(uint16_t port,uint8_t value);
void outw(uint16_t port,uint16_t value);
void outl(uint16_t port,uint32_t value);

uint8_t inb(uint16_t port);
uint16_t inw(uint16_t port);
uint32_t inl(uint16_t port);

#endif //PHANTOMOS_BUS_H
