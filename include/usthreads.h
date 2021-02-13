#ifndef __PHANTOMOS_2021_01_15_17_53_10
#define __PHANTOMOS_2021_01_15_17_53_10

///
/// An Opaque Type (in userspace) for which pointers to can be used to access any (kernel) thread of execution
typedef struct __ThreadHandle __ThreadHandle;

// ThreadHandle *GetCurrentThread(void);
// Gets a handle to the current thread. Returns NULL if the reference counter of the current thread exceeds 2^63-2 (which should never happen)
#define __NR_GetCurrentThread (256)

// _Noreturn void ThreadExit(int)
// Terminates the current thread with a status code.
// If this terminates the main thread of a process, the process exits with the same code
#define __NR_ThreadExit (257)

typedef struct __ThreadStartContext
{
    void *__th_stack;
    // A field for any internal use, generally by the platform library
    void *__th_internal;
    // First Param is __th_internal
    // Second Param is the Handle of the spawned thread
    // Third Param is fs:0
    int (*__th_start)(void *, __ThreadHandle *, void *);
} __ThreadStartContext;

// result StartThread(ThreadStartContext *,ThreadHandle**);
#define __NR_StartThread (258)

// result ParkThread(void);
// Blocks the calling thread until it's token is made available.
// If a token for the thread is already available, that token is consumed and the function returns immediately.
// Otherwise, the calling function will not resume until the token is made available,
//  the blocking timeout expires (returns TIMEOUT), or the thread is interrupted or signaled (returns INTERRUPTED).
// A successful return from ParkThread *synchronizes-with* any call to UnparkThread with the same
#define __NR_ParkThread (259)

// result UnparkThread(ThreadHandle *)
// Makes the token of the given thread available, and unblocks it if it is current blocked in a call to ParkThread
//
// Returns an INVALID_HANDLE if the thread handle is not a valid handle.
// Returns PERMISSION if the given handle designates a thread spawned by a different process, and the calling thread
//  does not have ThreadGeneral access to the thread designated by the handle
#define __NR_UnparkThread (260)

// result YieldThread(void);
// Yields the current thread back to the scheduler and causes it to be temporarily scheduled after all other threads of the same priority.
#define __NR_YieldThread (261)

// result AwaitAddress(void*);
// Blocks the current thread until the given address is signaled.
// Returns INVALID_ADDRESS if the parameter is not mapped, TIMEOUT if the blocking timeout expires, an INTERRUPTED if the thread is interrupted.
#define __NR_AwaitAddress (262)

// result SignalOne(void*);
#define __NR_SignalOne (263)

// result SignalAll(void*);
#define __NR_SignalAll (264)

// void SetBlockingTimeout(duration*)
// Causes the next call to a thread blocking function to return TIMEOUT after duration passes.
// The exact timing of the return is a best effort, but will not occur more than 1 second before the timeout expires.
//
#define __NR_SetBlockingTimeout (265)

// result SleepThread(const duration*)
// Blocks the current thread until duration expires, the blocking timeout expires if it is less, or the thread is interrupted.
// Returns TIMEOUT if the blocking timeout expires before the sleep duration ends, and INTERRUPTED if the thread is interrupted
#define __NR_SleepThread (266)

// result InterruptThread(ThreadHandle*)
// Interrupts the thread designated by the handle. If that thread is blocked by a system call,
//  then that system call returns INTERRUPTED immediately. Otherwise, the next system call
//  that thread makes which can be interrupted returns INTERRUPTED.
// This function *synchronizes-with* any system call that can be interrupted, as well as with any call to Interrupted.
// Returns INVALID_HANDLE if the handle is not a valid handle, and returns PERMISSION if the current thread does not have permission
//  to access that thread.
//
// A system call can be interrupted if it would cause the current thread to block, or is the system call Interrupted
#define __NR_InterruptThread (267)

// result Interrupted(void)
// Checks if the current thread has been interrupted by a call to InterruptThread,
//  and if so, returns INTERRUPTED, otherwise returns succesfully.
// This call does not block.
#define __NR_Interrupted (268)

// result JoinThread(ThreadHandle*)
// If the thread designated by the hande is terminated, then returns successfully.
//  Otherwise, blocks until that thread completes, the blocking timeout expires (TIMEOUT),
//  the current thread is interrupted (INTERUPTED), or the process the thread belongs to is terminated by a Signal or DestroyProcess (KILLED).
// A successful return from JoinThread also deatches the handle, as though by a call to DetachThreadHandle
//
// Returns INVALID_HANDLE if the handle is not a valid handle.
//
// If the thread exited by calling `ExitThread`, or returning from the thread starting function, with a positive integer argument, that value is returned to the caller of JoinThread
#define __NR_JoinThread (269)

// void ClearBlockingTimeout(void)
// Clears the current blocking timeout.

#define __NR_ClearBlockingTimeout (270)

// result GetProcessThreads(ProcessHandle* proc,ThreadHandle** out,unsigned long outsz)
// Gets a list of threads from running in a particular process.
// If proc is not NULL, then the running thread must be debugging the process designated by it,
//  or have Enumerate permission to it.
// If proc is NULL, then gets the threads running in the current process.
// If out is NULL, then returns the number of elements (with sizeof(ThreadHandle*)) that would have been stored in out.
// Otherwise, stores up to `outsz` elements into the array pointed to by out, and returns the number of elements stored,
//  where each element is a handle to a distinct thread running in the process designated by proc, or the current process.
//
// Returns INVALID_HANDLE if proc is neither NULL, nor a handle that can be accessed,
//  and ADDR if out is not in the address space of the calling thread.
#define __NR_GetProcessThreads (271)

// result DetachThreadHandle(ThreadHandle* th)
//
// Reclaims any reasources used by th. This should be called on all thread handles that aren't joined
#define __NR_DetachThreadHandle (272)

// result Pause(void)
//
// Blocks the current thread unconditionally. This function returns when the blocking timeout expires (TIMEOUT),
//  or the thread is interrupted (INTERRUPTED).
#define __NR_Pause (273)

#ifdef __PHANTOMOS_LIBS_SOURCE

#include <types.h>

#include <errors.h>

#ifdef __cplusplus
#define _Noreturn [[noreturn]]
extern "C"
{
#endif

    typedef struct __ThreadHandle ThreadHandle;

    typedef struct __ThreadStartContext ThreadStartContext;

    ThreadHandle *GetCurrentThread(void);

    _Noreturn void ExitThread(int);

    result StartThread(ThreadStartContext *, ThreadHandle **);

    result ParkThread(void);
    result UnparkThread(ThreadHandle *);

    result AwaitAddress(void *);
    result SignalOne(void *);
    result SignalAll(void *);

    result SetBlockingTimeout(const duration *);

    result Sleep(const thread *);

    result InterruptThread(ThreadHandle *);

    result Interrupted(void);

    result JoinThread(ThreadHandle *);

#ifdef __cplusplus
};
#endif

#endif

#endif /* __PHANTOMOS_2021_01_15_17_53_10 */