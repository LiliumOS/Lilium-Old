#ifndef PHANTOMOS_MEMCPY_H_2020_06_28_14_53
#define PHANTOMOS_MEMCPY_H_2020_06_28_14_53

#include <stddef.h>

void* memcpy(void* restrict dst,const void* restrict src,size_t sz);
void* memmove(void* dst,const void* src,size_t sz);

int memcmp(const void* a,const void* b,size_t sz);

int memset(void* dst,int chr,size_t sz);

#endif // defined(PHANTOMOS_MEMCPY_H_2020_06_28_14_53)