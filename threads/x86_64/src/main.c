#include <ThreadHandle.h>

void yield(void){
    __asm__ volatile("int $0x20"); // Return control to the scheduler
}

void deschedule(struct __ThreadHandle* __mixed th){
}
void reschedule(struct __ThreadHandle* __mixed th){}

