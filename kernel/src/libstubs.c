
_Noreturn void _hlt(){
    __builtin_unreachable();
}

void printk(const char* c,...){
    __builtin_unreachable();
}

