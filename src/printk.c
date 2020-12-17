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

#include <signal.h>
#include <stdatomic.h>

#include <screen.h>
#include <stdarg.h>

struct vram_entry{
    char asciz;
    unsigned char cl;
};

#define PRINTK_COLOR 0x0F

#define VRAM_MAX_X 80
#define VRAM_MAX_Y 25
#define TAB_STOP 4

extern volatile struct vram_entry __vram_start[VRAM_MAX_Y][VRAM_MAX_X];

static volatile sig_atomic_t x,y;

static volatile sig_atomic_t screenColor = PRINTK_COLOR;

static atomic_flag in_printk = ATOMIC_FLAG_INIT;

void clear(void){
    if(atomic_flag_test_and_set_explicit(&in_printk,memory_order_acquire))
        return;
    screenColor = PRINTK_COLOR;
    for(unsigned short y = 0;y<VRAM_MAX_Y;y++)
        for(unsigned short x = 0;x<VRAM_MAX_X;x++) {
            __vram_start[y][x].asciz = 0;
            __vram_start[y][x].cl = 0;
        }
    x = 0;
    y = 0;
    atomic_flag_clear_explicit(&in_printk,memory_order_release);
}

void putc(char c){
    if(atomic_flag_test_and_set_explicit(&in_printk,memory_order_acquire))
        return;
    if(c<' '||c==0x7F){
        switch(c){
            case '\n':
                x = 0;
                y++;
                break;
            case 8:
                x--;
                break;
            case 0x7F:
                __vram_start[y][x].asciz = 0;
                break;
            case '\r':
                x = 0;
                break;
            case '\t':
                do{
                    x++;
                }while(x%TAB_STOP!=0);
                break;
        }
    }else{
        __vram_start[y][x].cl = screenColor;
        __vram_start[y][x++].asciz = c;
    }
    if(x<0) {
        y--;
        x+=VRAM_MAX_X;
    }else if(x>=VRAM_MAX_X){
        y++;
        x-=VRAM_MAX_X;
    }

    if(y<0){ // I'll let this wrap, I don't want to deal with scrolling up
        x=0;
        y+=VRAM_MAX_Y;
    }else while(y>=VRAM_MAX_Y){ // While loop to scroll as much as necessary (should only need to scroll once)
            x=0;
            y--;
            for(int row = 1; row < VRAM_MAX_Y; row++) { // Start at one to not scroll into row -1
                for(int col = 0; col < VRAM_MAX_X; col++) {
                    __vram_start[row-1][col].cl = __vram_start[row][col].cl;
                    __vram_start[row-1][col].asciz = __vram_start[row][col].asciz;
                }
            }
            for(int col = 0; col < VRAM_MAX_X; col++) {
                __vram_start[VRAM_MAX_Y-1][col].cl = 0;
                __vram_start[VRAM_MAX_Y-1][col].asciz = 0;
            }
        }
    atomic_flag_clear_explicit(&in_printk,memory_order_release);
}

void printk(const char* c){
    if(atomic_flag_test_and_set_explicit(&in_printk,memory_order_acquire))
        return;
    for(;*c;c++){
        if(*c<' '||*c==0x7F){
            switch(*c){
                case '\n':
                    x = 0;
                    y++;
                break;
                case 8:
                    x--;
                break;
                case 0x7F:
                    __vram_start[y][x].asciz = 0;
                break;
                case '\r':
                    x = 0;
                break;
                case '\t':
                    do{
                        x++;
                    }while(x%TAB_STOP!=0);
                break;
                case '\x1b':
                    c++;
                    if(*c=='c')
                        clear();
                    else if(*c=='['){
                        //TODO
                    }
                break;
            }
        }else{
            __vram_start[y][x].cl = screenColor;
            __vram_start[y][x++].asciz = *c;
        }
        if(x<0) {
            y--;
            x+=VRAM_MAX_X;
        }else if(x>=VRAM_MAX_X){
            y++;
            x-=VRAM_MAX_X;
        }

        if(y<0){ // I'll let this wrap, I don't want to deal with scrolling up
            x=0;
            y+=VRAM_MAX_Y;
        }else while(y>=VRAM_MAX_Y){ // While loop to scroll as much as necessary (should only need to scroll once)
            x=0;
            y--;
            for(int row = 1; row < VRAM_MAX_Y; row++) { // Start at one to not scroll into row -1
                for(int col = 0; col < VRAM_MAX_X; col++) {
                    __vram_start[row-1][col].cl = __vram_start[row][col].cl;
                    __vram_start[row-1][col].asciz = __vram_start[row][col].asciz;
                }
            }
            for(int col = 0; col < VRAM_MAX_X; col++) {
                __vram_start[VRAM_MAX_Y-1][col].cl = 0;
                __vram_start[VRAM_MAX_Y-1][col].asciz = 0;
            }
        }


    }
    atomic_flag_clear_explicit(&in_printk,memory_order_release);
}


void vprintf(const char* fmt, va_list list){

}