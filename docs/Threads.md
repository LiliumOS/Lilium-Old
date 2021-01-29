# PhantomOS Threading

This document Describes how to create and manipulate PhantomOS kernel threads, 
 and the concurrency primitive operations provided by the PhantomOS kernel.

## Interrupting Threads

An Interruptable Operation is any operation that blocks execution of a thread within a system call, (IE. a waiting operation like `ParkThread`, `AwaitAddress`, or an blocking synchronous I/O operation).

[Note: Some operations may take time but are not considered blocking (and thus is not interruptable), for example, reading a large buffer from a Socket or Pipe that has sufficient bytes available is not a blocking operation. 
The threshold where a read/write operation is guaranteed to be considered blocking is not specified and may differ for each type of file, but exceeds the value of the `PIPE_BUF` macro.

A called to `YieldThread` does not block the thread, and is not interruptable.  ]

A thread may become interrupted in a number of ways:
* A call to `InterruptThread` is made, with a handle designating that thread.
* The thread recieves a signal that invokes a user-provided signal handler, and the Interruption Behaviour for that handler is to Interrupt the thread.
* Under the same rules as above, the signal handling thread of a process is interrupted when the process recieves a signal.
* A thread that has opened an IPC Channel recieved a message on that channel, and the channel is configured to Interrupt the thread.
* The thread is being debugged, and the debugging handle is used to set the interrupted flag of the thread.
* An asynchronous I/O operation started on the current thread completes or errors, and the I/O handle is configured to interrupt the thread. 

A thread that is interrupted while in a blocked state is resumed and the operation returns INTERRUPTED immediately, without continuing the operation. 
Otherwise, the next time a thread calls `Interrupted`, or performs an interruptable operation, that operation returns INTERRUPTED rather than performing the operation (but see notes under `ParkThread`). Whenever a system call returns INTERRUPTED, the interrupted flag is cleared. 

An operation that returns INTERRUPTED *synchronizes-with* an operation that interrupts the thread (except that when the flag is set directly by a debugger). Acquire-release semantics are guaranteed by the kernel.

There is no standard mechanism for interrupting the current thread. A thread that wishes to interrupt itself would need to call `InterruptThread(GetCUrrentThread())`. Calling `InterruptThread` with a NULL argument would return INVALID_HANDLE. 
In any case, Interrupting the current thread is generally incorrect, as interruption is used to indicate that a thread has some case that requires attention. If limiting the time blocked in an operation is desired, setting a blocking timeout may work better. 

## Blocking Timeout

Each thread has an internal value called it's Blocking Timeout. 
This places an approximate upper bound on the time it will spend blocked by an interruptable operation. 

[Note: This upper bound is not guaranteed, however, an operation will not timeout before the second the timeout would expire. Beyond this guarantee, the blocking timeout is on a best-effort basis.]

A thread may set its blocking timeout to any valid duration, with `SetBlockingTimeout`. The blocking timeout is cleared upon return from an interruptable operation (See note on `ParkThread`), or upon a call to `ClearBlockingTimeout`. 

If the blocking timeout expires while calling an interruptable operation, the thread resumes, and the operation returns TIMEOUT.

## Thread Errors

All thread calls that block the current thread return `INTERRUPTED` if they are interrupted, and `TIMEOUT` if the thread's blocking timeout expires. 

All thread calls that accept a `ThreadHandle*` argument return `INVALID_HANDLE` if the thread handle is not valid (IE. returned from `GetCurrentThread` or `GetProcessThreads`, or passed to the thread start function).

Additionally, all thread calls that accept a `ThreadHandle*` argument, except `DeatchThreadHandle`, return `PERMISSION` if called from a different process then the thread is executing in, when the calling thread does not have the appropriate access to that thread. 

All other errors are documented explicitly on the functions

## Functions
### GetCurrentThread

`ThreadHandle* GetCurrentThread()`

Returns a handle to the current thread. The handle must be passed to `DetachThreadHandle`.

This function always succeeds and thus does not return `result`. 
The return value is opaque, and cannot be safely dereferenced, ordered, or compared for equality. 

### ThreadExit

`_Noreturn void ThreadExit(int code);`

Completes the current thread normally, and reports the given code to any threads blocked in a call to `JoinThread`. 

If the current thread is the main thread of it's process,
  that process also exits with the same code.

If code is negative, the code reported to `JoinThread` and the process exit code is unspecified.

`ThreadExit` does not cause stack unwinding to occur, nor will it run destructors for thread-local variables. 

This function will not return to it's caller. 

### StartThread

`result StartThread(const ThreadStartContext* ctx,ThreadHandle** out)`

Spawns a new process in the current thread.

`ThreadStartContext` is a structure type declared as follows:
```c
typedef struct{
    void* th_stack;
    void* th_internal;
    int(*th_start)(void*,ThreadHandle*,void*);
} ThreadStartContext;
```

`th_stack` is the address to use as the head of the stack for that thread,
`th_internal` is a pointer field that has no further requirements, 
and `th_start` is the function called by the kernel in the new thread.

`th_start` is called with the value of `th_internal`, followed by a pointer to a handle for that thread, and finally a pointer to the start of the thread-local data segment.

The function returns `NO_MEMORY` if the necessary memory is not available or would exceed the calling processes virtual or physical memory limitations (and the calling thread does not have `AllocateExcess` permission). 
The function returns `PERMISSION` if the calling thread does not have `SpawnThread` permission to the current process, or the number of threads would exceed the thread limit and the calling thread does not have the `Limits` permission. 

If `out` is not NULL and it is not writable, or `ctx` or `ctx->th_stack` is not readable, returns `NOT_MAPPED`. 

If `ctx->th_start` is not executable, the newly spawned thread recieves `SIGSEGV`. 
If the signal is ignored, or the signal handler returns without mapping `th_start`, the thread immediately exits abnormally, and attempts to join the thread with `JoinThread` will return `KILLED`. 

If any other address error occurs (such as an alignment error), then `ADDRESS` is returned and the calling thread recieves `SIGBUS`. 

If `out` is not NULL, then stores a handle to the spawned thread in out. This handle must be joined with a call to `JoinThread`, or detached with a call to `DetachThreadHandle`. 

### ParkThread

`result ParkThread(void);`

If the calling thread's token is available, returns immediately. Otherwise, blocks until the calling thread's token is made available by a call to `UnparkThread`, the blocking timeout expires, or the thread is interrupted. 
A successful return from `ParkThread` *synchronizes-with* a call to `UnparkThread` that makes the calling thread's token available. Release-acquire semantics are guaranteed by the kernel. 

Notes:
* If the calling thread's token is available and the thread is interrupted at the time this function is called, it is unspecified whether the token is consumed and the function returns successfully, or if the interruption status is consumed and the function return INTERRUPTED. However, if the function returns successfully, the interruption status is not reset, and if it returns INTERRUPTED, the token is not consumed. 
* If the blocking timeout is set and the calling thread's token is available when this function is called, it is unspecified whether the blocking timeout is cleared.

### UnparkThread

`result UnparkThread(ThreadHandle* th)`

Makes the token of the thread `th` available, and unblocks it if it is blocked in a call to `ParkThread`. Otherwise, the token will be consumed the next time the thread calls `ParkThread`. If the token of `th` is already available, this call has no effect. 

A successful call to `UnparkThread` *synchronizes-with* a successful call to `ParkThread`. Release-acquire semantics are guaranteed by the kernel. 

### YieldThread

`void YieldThread(void)`

Yields the current thread back to the Scheduler, and temporarily orders it after all other threads with the same priority. 

This function is not considered to block the current thread, and is not interruptable. 

### AwaitAddress

`result AwaitAddress(void*)`

Blocks the current thread until the given address (granular to the page size) is signaled. 

Returns `NOT_MAPPED` if the given address is not mapped in the current process. 

### SignalOne

`result SignalOne(void*)`

Signals the given address (granular to the page size), and unblocks one random thread that is waiting on that address. 

Returns `NOT_MAPPED` if the given address is not mapped in the current process.

### SignalAll

`result SignalAll(void*)`

Signals the given address (granular to the page size), and unblocks all thread that are waiting on that address. 

### SetBlockingTimeout

`void SetBlockingTimeout(duration* timeout)`

Sets the blocking timeout of the current thread to the duration specified in `timeout`. 
This function always succeeds.

### SleepThread

`result SleepThread(duration* timeout)`

Blocks the thread until `timeout` has elapsed. 

[Note: Like all interruptable operations, the current thread will unblock early if interrupted or the blocking timeout expires. If the timeout and the blocking timeout are the same, it's unspecified whether the function returns successfully, or TIMEOUT]

### InterruptThread

`result InterruptThread(ThreadHandle* hdl)`

Interrupts `th` and unblocks it if it is blocked in the execution of an interruptable operation. 

### Interrupted

`result Interrupted(void)`

Checks if the current thread is interrupted, and returns INTERRUPTED if it is, or otherwise returns `0`. This function does not block the current thread, but will clear the interrupted status if it returns INTERRUPTED. 

A call to this function *synchronizes-with* an operation that sets the interrupted status of the current thread. Release-acquire semantics are guaranteed by the kernel

### JoinThread

`result JoinThread(ThreadHandle* th)`

If `th` has completed, returns the reported status code immediately or `0` if it completed abnormally (but see below for special cases), and releases the resources held by `th`. Otherwise, blocks until `th` completes, and returns the status code. 

If `th` exited due to a signal sent to the entire process which contains it, or that process was destroyed by a call to `DestroyProcess`, then `JoinThread` returns `KILLED` instead of a status code. The resources are still reclaimed. 
If starting the thread delivered a `SIGSEGV` that killed the thread (but not the surrounding process), JoinThread will also return `KILLED`. This occurs even if the signal was ignored, or a user-provided signal handler returned without mapping the start address. 

### ClearBlockingTimeout

`void ClearBlockingTime(void)`

Clears the thread blocking timeout. 

### DetachThreadHandle

`result DeatchThreadHandle(ThreadHandle* th)`

Detaches the thread designated by `th` from that handle. After this, use of `th` is not permitted. 

### Pause

`result Pause(void)`

Blocks the current thread until it is interrupted or the blocking timeout expires. This function will not return successfully. 
