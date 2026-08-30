#ifndef ASTERION_H
#define ASTERION_H

#include <stddef.h>
#include <stdint.h>

#define ASTERION_NAME "Asterion"
#define ASTERION_VERSION "0.1.0-kernel-foundation"
#define ASTERION_MAX_PROCESSES 32
#define ASTERION_MAX_SYSCALLS 64
#define ASTERION_MAX_MOUNTS 8
#define ASTERION_PAGE_SIZE 4096u

typedef enum {
    AST_OK = 0,
    AST_ERR_INVALID = -1,
    AST_ERR_FULL = -2,
    AST_ERR_NOT_FOUND = -3,
    AST_ERR_PERMISSION = -4,
    AST_ERR_UNSUPPORTED = -5
} ast_status_t;

typedef enum {
    PROC_UNUSED = 0,
    PROC_READY,
    PROC_RUNNING,
    PROC_BLOCKED,
    PROC_ZOMBIE
} process_state_t;

typedef struct {
    uint32_t pid;
    char name[32];
    process_state_t state;
    uint8_t priority;
    uint32_t ticks;
} process_t;

typedef struct {
    uint64_t total_pages;
    uint64_t used_pages;
    uint64_t high_watermark;
} page_allocator_t;

typedef struct {
    const char *name;
    const char *mountpoint;
    uint32_t flags;
} filesystem_mount_t;

typedef ast_status_t (*syscall_handler_t)(uint64_t, uint64_t, uint64_t, uint64_t);

typedef struct {
    uint32_t number;
    const char *name;
    syscall_handler_t handler;
} syscall_entry_t;

void console_write(const char *message);
void console_write_line(const char *message);
void kernel_panic(const char *reason);

void page_allocator_init(page_allocator_t *allocator, uint64_t bytes);
ast_status_t page_alloc(page_allocator_t *allocator, uint64_t count);
ast_status_t page_free(page_allocator_t *allocator, uint64_t count);

void process_table_init(void);
ast_status_t process_create(const char *name, uint8_t priority, uint32_t *pid_out);
process_t *process_get(uint32_t pid);
uint32_t process_count(void);

void scheduler_init(void);
ast_status_t scheduler_tick(uint32_t *running_pid);
ast_status_t scheduler_block(uint32_t pid);
ast_status_t scheduler_unblock(uint32_t pid);

void syscall_init(void);
ast_status_t syscall_register(uint32_t number, const char *name, syscall_handler_t handler);
ast_status_t syscall_invoke(uint32_t number, uint64_t a, uint64_t b, uint64_t c, uint64_t d);

void vfs_init(void);
ast_status_t vfs_mount(const char *name, const char *mountpoint, uint32_t flags);
uint32_t vfs_mount_count(void);
const filesystem_mount_t *vfs_mount_at(uint32_t index);
void astfs_init(void);

#endif
