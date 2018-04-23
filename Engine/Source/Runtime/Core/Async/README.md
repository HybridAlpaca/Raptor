## Async

This set of utilities is defined in order to allow for any of three tasks, increasing in complexity:

- (One) The ability to parallelize engine operations in order to utilize the most of the end user's CPU
and to increase general performance of the engine.

- (Two) To provide a generalized task structure which defines how specific engine operations should be
carried out, using the basis of (One) to provide parallelization to said operations.

- (Three) Provide an easy to learn / use interface for both (One) and (Two), such that the jobs system
may be employed at any arbitrary point in the engine, in any user-defined engine plugin or addon, or in
any user defined game code.

### Why We Need It

Multithreading is at the very core of c++ efficiency.  The ability to utilize all of a CPU's arithmetical
prowess is a key fundamental to achieving maximum power for an application, but oftentimes this ability
can be misused or abused in ways that would otherwise harm the application.  The Raptor Core's async module
automates the difficult duty of creating, managing, and freeing processes on the CPU core ("threads") and
their associated context ("fibers").

### How It Works

During engine startup, one of the first things that is done is to set up the async system.  This entails
three things:

- (1) Enumerating each of the user's logical CPU cores,
- (2) Creating and binding a thread to each of those cores,
- (3) Create a pool of idle fibers for later use, and
- (4) Initialize a task manager (the "job system") with the threads and fibers.

Threads, in this context, act as the true powerhouses: they act as the virtual areas of execution for each
of the engine's tasks.  Due to how each thread is locked to a CPU core, the issue of thread context switches
has essentially been eliminated.  Each thread is capable of performing any task (within a reasonable extent)
that the game may throw at it, but where are these tasks?  The answer is in the fibers.

Whenever an engine module needs something to be done within the current frame or within a specified number
of frames, it creates a task for that operation on the job system.  The job system will then pull a fiber
out of its fiber pool, and bind that task (in the form of a function) to said fiber and place it on a queue.
For each of the user's CPU cores, the thread bound to that core will continuously operate on the fibers in
that queue in the following way:

- Pop fiber A from the queue pool and step into task function
- Begin execution of fiber A until it runs into dependancies: now, B C & D must be completed in order for A
to continue operation
- Store the thread's registers, instruction pointer and stack pointer inside thread A (remember, a fiber is
just a context for function execution!) and place A on a separate queue (a "waiting list")
- Begin task E until the thread encounters dependancies
- By now, other threads have completed tasks B C & D.  Pop task A from the waiting list and resume execution

As you can see, this very simple yet _extremely_ effective mechanism for performing tasks can be employed
to produce as much efficiency as possible.  In addition, it takes almost no time or effort to swap a thread's
current fiber; in contrast to a full-on thread context switch, it simply dumps its registers, IP & SP into
the fiber.