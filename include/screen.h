// screen.h
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

#ifndef PHANTOMOS_SCREEN_H
#define PHANTOMOS_SCREEN_H

#include <stdarg.h>

void clear(void);

void printk(const char*);

void putc(char);

void printf(const char*,...);
void vprintf(const char*,va_list);

typedef enum{
    hh = 'hh', // yes, yes it is
    h = 'h',
    def = 0,
    l = 'l',
    ll = 'll',
    j = 'j',
    z = 'z',
    L = 'L'
} length;

typedef struct {
    va_list* list;
    int width;
    int precision;
    length len;
} format_state;

void add_formatter(char name,void(*fmt)(format_state));

#endif //PHANTOMOS_SCREEN_H
