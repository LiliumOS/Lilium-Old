# PhantomOS

PhantomOS supports all POSIX signals, including 32 POSIX Realtime Signals. 
The semantics of signals, and the relevant system calls, are documented here.

## Signal Actions

Every Signal has one of 6 actions, that applies to the recieving thread (and in some cases, the process of the recieving thread):
- Ignore the signal
- Execute a user-defined signal handler
- Abnormally Terminate the Thread
- Abnormally Terminate the Thread, and (if enabled) produce a core dump
- Place the Thread into the STOPPED state
- Return a Thread from a STOPPED state to a RUNNING state.

The last four actions are referred to as default actions, respectively, a default action of terminate, a default action of core dump, a default action of stop, and a default action of continue. 

By default, the disposition of a signal on the thread either is to ignore the signal, or execute one of the 4 default actions (which is the case is signal-specific). 
Additionally, the dispositions of the 3 "unblockable" signals (SIGKILL, SIGSTOP, SIGCONT) are fixed to the default action (terminate, stop, or continue; respectively), and this cannot be changed. Additionally, these signals are special-cased when a signal is delivered to a process (rather than a thread). 

## Signal State Flags

Each thread has a flag that controls how default actions apply, the signal action flag. 
By default, this flag is set, and default actions apply to both the thread and it's controlling process. 
In particular, with the flag set:
* Executing a default action of terminate or core dump on a thread abnormally terminate the process. Note that terminating the main thread with a signal will also cause abnormal termination of the process, **even** if the main thread has cleared the flag.
* Executing a default action of stop on a thread will place both the thread and the process into the STOPPED state.
* Executing a default action of continue on a thread will place the thread and the process into the RUNNING state if it was previously in the STOPPED state. This will **not** place other threads in a STOPPED state into the RUNNING state (with exceptions detailed in the "Signal Handling Thread" section)

If the flag is cleared, then default actions applies only to the thread (with exceptions detailed in the "Signal Handling Thread" section).

Additionally, each thread has a flag that controls whether the executing a signal handler interrupts the thread, the signal interrupt flag. This flag is also set by default. When set, after receiving a signal, the thread is interrupted:
* When returning from a user-provided signal handler
* When executing a default action of continue (even if the thread was not STOPPED).
* 
If the flag is clear, then the thread is *never* interrupted upon reciept of a signal. 

## Signal Handling Thread

Every process has a signal handling thread. When the process is created, or `exec`s, this is set to the main thread. 
Whenever a process recieves a signal, the result is equivalent to the signal handling thread of the process recieving the same signal, except:
* If the signal recieved is SIGKILL or SIGSTOP, then the signal action flag is ignored for the purposes of handling that signal, and both the signal handling thread, and it's controlling process are termianted or stopped. 
* If the signal recieved is SIGCONT, then both the process, and *every* thread in the process that is in a STOPPED state is put into a RUNNING state. Only the Signal Handling Thread is interrupted, however, if its signal interrupt flag is set.

## Signal Receipt

Whether or not a signal is received by a thread depends on it's state, and on the action to be executed. No signals are received by a thread that is in a DEAD state, nor are signals that execute an action of ignore received. For all other states:
* A thread in the RUNNING or BLOCKED state will recieve any thread, and execute the action according to the "Signal Delivery" rules (documented in the following section).
* A thread in the STOPPED or SUSPENDED state will recieve any signal that executes a default action (Notably: A default action of continue is executed, even for a SUSPENDED thread; this may interrupt that thread)
* A thread in the ALIVE state will recieve only signals that execute a default action of terminate or core dump.
* A thread in the init process will recieve only signals that execute a user-provided signal handler or that executes a default action of continue. The signal action flag is treated as clear when executing a default action of continue or such threads. 
    * The signal handling thread in the init process will not recieve a signal that executes a default action of continue, when the signal is sent to the process. Whether or not such signals are recieved by the thread when sent to the thread specifically is unspecified. 

## Signal Delivery and Resumable System Calls

When a signal is sent to a thread, except by from that thread itself, PhantomOS only guarantees that the signal will be recieved in a finite amount of time. Specifically, PhantomOS delivers signals to a thread at the following points in it's execution, when the state of the thread permits the receipt of the signal:
* Immediately, if the signal is delivered as the result of a fault caused by that thread.
* Immediately before any system call executed on that thread returns to userspace
* Immediately before a System call executed on that thread puts the thread into a BLOCKED state.
* To any thread that is BLOCKED, STOPPED, or SUSPENDED, within some finite period of time. 
* Immediately before control is returned to the thread from the scheduler. 

## Signals

The following signals are defined by PhantomOS, with the given signal ID, and given default action

|Signal | No. | Action        |
|-------|-----|---------------|
|SIGHUP | 1   | Terminate     |
|SIGINT | 2   | Terminate     |
|SIGQUIT| 3   | Terminate     |
|SIGILL | 4   | Core Dump     |
|SIGTRAP| 5   | Core Dump**   |
|SIGABRT| 6   | Core Dump     |
|SIGFPE | 7   | Core Dump     |
|SIGKILL| 9   | Terminate*    |
|SIGUSR1| 10  | Terminate     |
|SIGSEGV| 11  | Core Dump     |
|SIGUSR2| 12  | Terminate     |
|SIGPIPE| 13  | Terminate     |
|SIGALRM| 14  | Terminate     |
|SIGTERM| 15  | Terminate     |
|SIGCHLD| 16  | Ignore        |
|SIGCONT| 17  | Continue*     |
|SIGSTOP| 18  | Stop*         |
|SIGTSTP| 19  | Stop          |
|SIGTTIN| 20  | Stop          |
|SIGTTOU| 21  | Stop          |
|SIGURG | 22  | Ignore        |
|SIGXCPU| 23  | Core Dump     |
|SIGXFSZ| 24  | Core Dump     |
|SIGVTALRM| 25| Terminate     |
|SIGPROF| 26  | Terminate     |
|SIGWINCH| 27 | Ignore        |
|SIGSYS | 28  | Core Dump     |

*: Signal is unblockable, and then default behaviour cannot be changed.

**: SIGTRAP is intercepted by the active Debugger for the thread, if any. If a debugger intercepts the signal, it is not delivered to the thread, but the thread is instead SUSPENDED. 

SIGWINCH is not specified by POSIX.

PhantomOS does not specify the result of returning from a user-defined signal handler executed as the result of recieving a SIGILL, SIGFPE, or SIGBUS that was sent as the result of a fault on the recieving thread. 
PhantomOS does not specify the result of returning from a SIGSEGV delivered to a thread before it's initial function is called. 

## Signal Syscalls

### SIG_FLG_ACTION

`#define SIG_FLG_ACTION /*unspecified*/`

This macro is defined to a value of type `long` that is not negative, and may be passed to `SetSignalFlags` (potentially `|` `SIG_FLG_INTERRUPT`) or `ClearSignalFlags`, to set or clear the signal action flag.

### SIG_FLG_INTERRUPT

This macro is defined to a value of type `long` that is not negative, and may be passed to `SetSignalFlags` (potentially `|` `SIG_FLG_ACTION`) or `ClearSignalFlags`, to set or clear the signal interrupt flag.

### SignalThread / SignalProcess

`result SignalThread(ThreadHandle* hdl,int sig);`
`result SignalProcess(ProcessHandle* hdl,int sig);`

For `SignalThread`, sends an asynchronous signal to the thread designated by `hdl`, or the calling thread if `hdl` is `NULL`. 
(If the signal is sent to the current thread, it is recived as a synchronous signal instead, unless executed from the handler of the same signal).
For `SignalProcess`, sends an asynchronous signal to the signal handling thread of the process designated by `hdl`, or the current process if `hdl` is `NULL`. 

This system call is *memory coherent*. An Atomic access `A` on a thread of execution that calls `SignalThread` that is *sequenced-before* the call *strongly happens-before* that call. 

Returns INVALID_HANDLE if `hdl` is neither NULL nor a valid thread handle (or process handle). Returns INVALID_ARGUMENT if `sig` is not a signal number defined above, or a real-time signal.
Returns PERMISSION if the current thread does not have `SendSignal` permission to `hdl`. 

### signal

`void (*signal(int sig, void (*handler) (int))) (int)`

Registers the given `handler` to handle `sig` on the calling thread. Returns the previously registered signal handler, or SIG_ERR if an error occurs.

If `handler` is not mapped when this function is called, and is neither SIG_DFL nor SIG_IGN, returns SIG_ERR. 
If `handler` is mapped when the function is called, but is unmapped from the calling thread's address space, the calling thread recieves SIGSEGV. If the SIGSEGV handler is unmapped at this time, the calling thread recieves SIGKILL.

If `sig` is not a valid signal number, or is `SIGKILL`, `SIGSTOP`, or `SIGCONT`, returns SIG_ERR.

### SetSignalFlags

`result SetSignalFlags(long flags);`

flags shall be some combination of `SIG_FLG_ACTION`, and `SIG_FLG_INTERRUPT` (combined with or).

If `SIG_FLG_ACTION` is set in `flags`, then the signal action flag is set. If `SIG_FLG_INTERRUPT` is set in `flags`, then the signal interrupt flag is set. 

The total operation shall behave as though an atomic read-modify-write with memory_order_relaxed. 

Returns INVALID_ARGUMENT if flags is neither `SIG_FLG_ACTION`, nor `SIG_FLG_INTERRUPT`, nor `SIG_FLG_ACTION|SIG_FLG_INTERRUPT`. Returns PERMISSION if `SIG_FLG_ACTION` is specified, and the calling thread does not have SendSignal permission to the current process. If an error is returned, then no flags were modified by the call.

### ClearSignalFlags

`result ClearSignalFlags(long flags);`

flags shall be some combination of `SIG_FLG_ACTION`, and `SIG_FLG_INTERRUPT` (combined with or).

If `SIG_FLG_ACTION` is set in `flags`, then the signal action flag is cleared. If `SIG_FLG_INTERRUPT` is set in `flags`, then the signal interrupt flag is cleared. 

The total operation shall behave as though an atomic read-modify-write with memory_order_relaxed. 

Returns INVALID_ARGUMENT if flags is neither `SIG_FLG_ACTION`, nor `SIG_FLG_INTERRUPT`, nor `SIG_FLG_ACTION|SIG_FLG_INTERRUPT`. If an error is returned, then no flags were modified by the call.

### SetHandlingThread

`result SetHandlingThread(ThreadHandle* hdl);`

Sets the signal handling thread of the current process to `hdl`, or the current thread if `hdl` is NULL. 

Returns INVALID_HANDLE if `hdl` is neither NULL nor a valid ThreadHandle. Returns INVALID_ARGUMENT if `hdl` is a handle to a thread that is not owned by the current process. If `hdl` is not NULL, returns PERMISSION if the calling thread does not have `SendSignal` permission to `hdl`. Returns PERMISSION if the calling thread does not have `SignalControl` permission to the current process.


