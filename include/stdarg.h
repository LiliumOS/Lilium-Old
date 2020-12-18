#ifndef __PHANTOMOS_STDARG_H_2020_12_17_19_28_34 
#define __PHANTOMOS_STDARG_H_2020_12_17_19_28_34

typedef __builtin_va_list va_list;
#define va_start(ap,arg) __builtin_va_start(ap,arg)
#define va_end(ap) __builtin_va_end(ap)
#define va_copy(ap1,ap2) __builtin_va_copy(ap1,ap2)

#define va_arg(ap,type) __builtin_va_arg(ap,type)

#endif