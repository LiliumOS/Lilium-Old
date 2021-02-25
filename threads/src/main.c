
#include <ThreadHandle.h>
#include <errors.h>
#include <limits.h>

#define SYSCALL(v) ((void(*)(void))(v))



__ThreadHandle* sys_GetCurrentThread(void){
    if(atomic_fetch_add_explicit(&self->ref_count,1,memory_order_relaxed)==ULONG_MAX){
        // FIXME: I'm pretty sure this is a race condition, but idk how to make it not be one, without a CAS Loop
        atomic_fetch_sub_explicit(&self->ref_count,1,memory_order_relaxed);
        return NULL;
    }
    else
        return self;
}

result block_condition(_Bool(* __kernel callback)(struct __ThreadHandle*)){
    do{
        enum ThreadStatus status = atomic_load_explicit(&self->status,memory_order_relaxed);
        while(status==Suspended||status==Stopped){
            yield(); // If we are suspended by a debugger, or stopped by a signal, then yield back to the scheduler.
            status = atomic_load_explicit(&self->status,memory_order_relaxed);
        }

        if(atomic_flag_test_and_set_explicit(&self->inv_interrupted,memory_order_acquire))
            return __ERROR_THINTERRUPTED;
        
        if(callback(self))
            return 0;
        else{
            deschedule(self);
            atomic_store_explicit(&self->status,Blocked,memory_order_relaxed);
        }
    }while(1);

}

_Bool thread_is_parked(struct __ThreadHandle* th){
    return atomic_flag_test_and_set_explicit(&th->inv_token,memory_order_acquire);
}

void unpark_thread(struct __ThreadHandle* __mixed th){
    atomic_flag_clear_explicit(&th->inv_token,memory_order_release);
}

result sys_ParkThread(void){
    return block_condition(thread_is_parked);
}

void interrupt_thread(struct __ThreadHandle* __mixed th){
    atomic_flag_clear_explicit(&th->inv_interrupted,memory_order_release);
    enum ThreadStatus blocked = Blocked;
    if(atomic_compare_exchange_strong_explicit(&th->status,&blocked,Running,memory_order_acquire,memory_order_relaxed)){
        reschedule(th);
    }
}


__attribute__((visibility("default"), used, section(".syscall"))) void (*syscalls[])(void) = {
    SYSCALL(sys_GetCurrentThread),
    NULL,
    NULL,
    SYSCALL(sys_ParkThread)
};

__attribute__((visibility("default"), used)) long syscall_base = 0x100;
