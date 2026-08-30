# System-call ABI

The syscall table is intentionally explicit and versionable. Planned calls include read, write, open, close, fork, exec, exit, wait, mmap, munmap, socket, connect, send, recv, getpid, and sleep. Each call must validate user pointers, document ownership, and return an Asterion status code.

The current registry is a hosted/freestanding foundation, not a CPU instruction entry path.
