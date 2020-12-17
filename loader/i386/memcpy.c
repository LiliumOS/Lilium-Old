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

#include <stddef.h>

void* memcpy(void* restrict dst,const void* restrict src,size_t sz){
    for(size_t s = 0;s<sz;s++)
        ((unsigned char*)dst)[s] = ((const unsigned char*)src)[s];
    return dst;
}

void* memmove(void* dst,const void* src,size_t sz){
    for(size_t s = 0;s<sz;s++)
        ((unsigned char*)dst)[s] = ((const unsigned char*)src)[s];
    return dst;
}

void* memset(void* dst,int b,size_t sz){
    for(size_t s = 0;s<sz;s++)
        ((unsigned char*)dst)[s] = (unsigned char)b;
    return dst;
}