#include <MachineInfo.h>
#include <usthreads.h>

#include <stdint.h>
#include <memory.h>

#include <stdatomic.h>
#include <types.h>

enum ThreadStatus{
    Alive = 0,
    Running = 1,
    Blocked = 2,
    Suspended = 3,
    Stopped = 4,
    Finished = 5,
    Dead = 6,
    Zombie = 7
};

struct __ThreadHandle{
    atomic_uint_least64_t ref_count;        
    _Atomic(enum ThreadStatus)  status;
    atomic_flag inv_token;
    atomic_flag inv_interrupted;
    duration timeout_dur;
    uint32_t priority;
    _Atomic(void* __user) waiting_address;
    struct __ProcessHandle* proc;
};

extern struct __ThreadHandle* __mixed self; 

void deschedule(struct __ThreadHandle* __mixed th);
void reschedule(struct __ThreadHandle* __mixed th);

void yield(void);

result block_condition(_Bool(* __mixed callback)(struct __ThreadHandle*));

void interrupt_thread(struct __ThreadHandle* __mixed th);

void unpark_thread(struct __ThreadHandle* __mixed tb);