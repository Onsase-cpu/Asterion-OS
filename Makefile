CC = gcc
AS ?= as
LD ?= ld
CFLAGS := -std=c11 -Wall -Wextra -Werror -Iinclude -Ikernel -Iuserland
HOSTED_CFLAGS := $(CFLAGS) -DHOSTED
KERNEL_CFLAGS := -std=c11 -ffreestanding -fno-stack-protector -fno-pie -mno-red-zone -Wall -Wextra -Werror -Iinclude -Ikernel
BUILD := build

HOSTED_SRCS := tools/hosted_shell.c kernel/memory/page_frames.c kernel/process/process.c kernel/scheduler/scheduler.c kernel/filesystem/vfs.c kernel/filesystem/astfs.c userland/shell/commands.c
HOSTED_OBJS := $(patsubst %.c,$(BUILD)/hosted/%.o,$(HOSTED_SRCS))
KERNEL_SRCS := kernel/libc.c kernel/main.c kernel/memory/page_frames.c kernel/process/process.c kernel/scheduler/scheduler.c kernel/filesystem/vfs.c kernel/filesystem/astfs.c kernel/syscall/syscall.c kernel/security/security.c
KERNEL_OBJS := $(patsubst %.c,$(BUILD)/kernel/%.o,$(KERNEL_SRCS))

.PHONY: all hosted test kernel clean format
all: hosted

hosted: $(BUILD)/asterion-shell

$(BUILD)/asterion-shell: $(HOSTED_OBJS)
	@mkdir -p $(@D)
	$(CC) $(HOSTED_CFLAGS) -o $@ $^

$(BUILD)/hosted/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(HOSTED_CFLAGS) -c $< -o $@

kernel: $(BUILD)/asterion.elf

$(BUILD)/asterion.elf: $(KERNEL_OBJS) $(BUILD)/kernel/boot/entry.o
	@mkdir -p $(@D)
	$(LD) -nostdlib -z max-page-size=0x1000 -T boot/linker.ld -o $@ $^

$(BUILD)/kernel/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(KERNEL_CFLAGS) -c $< -o $@

$(BUILD)/kernel/boot/entry.o: boot/entry.S
	@mkdir -p $(@D)
	$(AS) --64 $< -o $@

test: hosted
	$(CC) $(HOSTED_CFLAGS) tests/kernel_tests.c kernel/memory/page_frames.c kernel/process/process.c kernel/scheduler/scheduler.c kernel/filesystem/vfs.c kernel/filesystem/astfs.c -o $(BUILD)/kernel-tests
	$(BUILD)/kernel-tests

format:
	clang-format -i $$(find . -name '*.c' -o -name '*.h') 2>/dev/null || true

clean:
	rm -rf $(BUILD)
