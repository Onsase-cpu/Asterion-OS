# Boot flow

The intended first boot target is UEFI plus a pinned Limine release. The kernel entry object currently demonstrates the freestanding handoff boundary and links into an ELF image. Image assembly, Limine binaries, memory-map parsing, framebuffer handoff, and QEMU smoke testing are next milestones.
