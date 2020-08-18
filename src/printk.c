//
// Created by chorm on 2020-07-21.
//

#include <signal.h>

struct vram_entry{
    char asciz;
    unsigned char cl;
};

#define PRINTK_COLOR 0x0F

#define VRAM_MAX_X 80
#define VRAM_MAX_Y 25

extern volatile struct vram_entry __vram_start[VRAM_MAX_Y][VRAM_MAX_X];

static volatile sig_atomic_t x,y;

void clear(void){
    for(unsigned short y = 0;y<VRAM_MAX_Y;y++)
        for(unsigned short x = 0;x<VRAM_MAX_X;x++) {
            __vram_start[y][x].asciz = 0;
            __vram_start[y][x].cl = 0;
        }
    x = 0;
    y = 0;
}

void printk(const char* c){
    for(;*c;c++){
        if(*c<' '||*c==0x7F){
            switch(*c){
                case '\n':
                    x = 0;
                    y++;
                break;
                case 0x7F:
                    x--;
                break;
            }
        }else{
            __vram_start[y][x].cl = PRINTK_COLOR;
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
                __vram_start[0][col].cl = 0;
                __vram_start[0][col].asciz = 0;
            }
        }
    }
}
