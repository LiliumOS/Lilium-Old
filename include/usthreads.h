#ifndef __PHANTOMOS_2021_01_15_17_53_10
#define __PHANTOMOS_2021_01_15_17_53_10

///
/// An Opaque Type (in userspace) for which pointers to can be used to access any (kernel) thread of execution
typedef struct ThreadHandle ThreadHandle;

// ThreadHandle *GetCurrentThread(void);
#define __NR_GetCurrentThread (100)

// void ThreadExit()
#define __NR_ThreadExit (101)

typedef struct ThreadStartContext
{
    void *th_stack;
    // A field for any internal use, generally by the platform library
    void *__th_internal;
    // First Param is __th_internal
    // Second Param is the Handle of the spawned thread
    // Third Param is fs:0
    void (*th_start)(void *, ThreadHandle *, void *);
} ThreadStartContext;

// ThreadHandle *StartThread(ThreadStartContext *);
#define __NR_StartThread (102)

#endif /* __PHANTOMOS_2021_01_15_17_53_10 */