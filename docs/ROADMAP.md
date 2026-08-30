# Roadmap

## Foundation
Boot protocol integration, serial logging, physical page allocator, virtual-memory page tables, GDT/IDT, timer interrupts, process address spaces, context switching, preemptive scheduling, and a real syscall entry path.

## Storage and devices
ASTFS on a block-device abstraction, VFS path resolution, FAT32/ISO9660 readers, PCI enumeration, framebuffer, keyboard, mouse, virtio storage, and QEMU image automation.

## User space
A minimal libc, ELF loader, pipes, signals, permissions, shell utilities, package metadata, and a window server.

## Networking
Ethernet, ARP, IPv4, ICMP, UDP, TCP, DNS, and an HTTP client, each behind testable interfaces.
