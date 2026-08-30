# Asterion OS

Asterion is a modular 64-bit operating-system research project for x86-64 PCs. It is designed to make kernel concepts readable while growing toward a complete desktop system: boot, CPU setup, memory, processes, scheduling, system calls, VFS, ASTFS, drivers, networking, security, and user-space tools.

> A modern 64-bit operating system engineered from the kernel upward.

## Current milestone

This repository delivers the **Asterion Kernel Foundation**. It contains a clean hybrid-kernel layout, a freestanding kernel entry path, serial and framebuffer-friendly logging boundaries, page-frame accounting, process metadata, a round-robin scheduler model, a syscall registry, VFS/ASTFS interfaces, driver contracts, security primitives, a user-space shell registry, a hosted shell harness, tests, and architecture documentation.

It is intentionally honest about scope. A full operating system needs sustained hardware work, bootloader integration, drivers, validation on real machines, security review, and extensive testing. The included hosted harness is an educational development tool, not an emulator and not proof of hardware readiness.

## Repository map

| Area | Purpose |
|---|---|
| `boot/` | Boot protocol notes and freestanding entry boundary |
| `arch/x86_64/` | x86-64 CPU and low-level platform interfaces |
| `kernel/` | Kernel subsystems with narrow interfaces |
| `userland/` | Shell, libc boundary, and future utilities |
| `include/` | Shared kernel ABI and public data contracts |
| `tools/` | Hosted development harnesses and validation helpers |
| `docs/` | Architecture and roadmap documentation |
| `tests/` | Hosted unit tests for deterministic subsystems |
| `config/` | Boot and build configuration |

## Build the hosted harness

```sh
make hosted
./build/asterion-shell
make test
```

The harness exposes a small command shell with `help`, `ps`, `mem`, `mounts`, `uname`, and `clear`. It exercises the same conceptual scheduler, memory, process, and VFS models used by the kernel foundation.

## Build the freestanding kernel object

```sh
make kernel
```

This compiles the kernel objects and produces `build/asterion.elf` when a freestanding x86-64 GCC/binutils toolchain is available. Creating a bootable disk image is intentionally a separate milestone because it requires a pinned bootloader artifact, image assembly, and QEMU validation.

## Design principles

Asterion keeps architecture boundaries explicit. The kernel owns privileged state; user space interacts through syscall contracts; VFS hides filesystem implementations; ASTFS is one filesystem provider rather than the whole storage story; drivers expose capabilities behind narrow interfaces; and every subsystem can be tested in a hosted environment before hardware bring-up.

## Safety and status

Asterion is an educational research operating system. It is not suitable for production workloads, secure data, or safety-critical control. Hardware support, networking, security hardening, and GUI functionality remain roadmap work.
