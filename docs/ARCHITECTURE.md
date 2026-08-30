# Asterion architecture

Asterion uses a modular hybrid-kernel direction. Privileged services remain in kernel space behind narrow interfaces, while user-space programs access them through explicit syscall contracts. The repository is split by responsibility so a future GUI, networking stack, and developer SDK can evolve without coupling to low-level implementation details.

## Layering

Hardware enters through boot and architecture code. The kernel coordinates CPU, memory, interrupts, scheduling, process metadata, IPC, drivers, VFS, ASTFS, networking, and security. Userland depends on stable headers and syscall numbers rather than reaching directly into kernel internals. Hosted tests compile deterministic subsystem models without claiming to emulate hardware.

## Ownership rules

The memory manager owns page accounting. The scheduler owns runnable state. The process table owns PID metadata. VFS owns mount routing and ASTFS owns its filesystem provider. Syscalls are the only public kernel boundary intended for applications.
