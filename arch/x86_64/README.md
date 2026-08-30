The x86-64 layer owns CPU tables, interrupt entry, context switching, APIC/timer bring-up, and platform discovery. Keep architecture-specific code behind portable kernel interfaces.
