//
// Created by chorm on 2020-07-21.
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