//
// Created by chorm on 2020-09-28.
//

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
