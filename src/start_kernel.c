//
// Created by chorm on 2020-07-21.
//

void printk(const char* v);

void start_kernel(struct multiboot* multiboot){
    (void)multiboot;
    printk("Hello World\n");

    for(;;);
}