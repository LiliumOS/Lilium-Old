//
// Created by chorm on 2020-07-21.
//

void printk(const char* v);

_Noreturn __attribute__((section(".text.init"))) void start_kernel(void* multiboot){
    (void)multiboot;
    printk("Hello World\n");

    for(;;);
}