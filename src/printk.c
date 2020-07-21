//
// Created by chorm on 2020-07-21.
//

struct vram_entry{
    char asciz;
    unsigned char cl;
};

#define PRINTK_COLOR 0x0F

#define VRAM_MAX_X 80
#define VRAM_MAX_Y 25

extern volatile struct vram_entry __vram_start[VRAM_MAX_X][VRAM_MAX_Y];

static short x,y;

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
            __vram_start[x][y].cl = PRINTK_COLOR;
            __vram_start[x++][y].asciz = *c;
        }
        if(x<0) {
            y--;
            x+=VRAM_MAX_X;
        }else if(x>VRAM_MAX_X){

        }
    }
}
