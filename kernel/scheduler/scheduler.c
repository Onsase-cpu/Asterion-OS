#include "asterion.h"

static uint32_t current_pid;

void scheduler_init(void) { current_pid = 0; }

ast_status_t scheduler_tick(uint32_t *running_pid) {
    uint32_t start = current_pid;
    for (uint32_t step = 1; step <= ASTERION_MAX_PROCESSES; ++step) {
        uint32_t candidate = ((start + step - 1) % ASTERION_MAX_PROCESSES) + 1;
        process_t *process = process_get(candidate);
        if (process && (process->state == PROC_READY || process->state == PROC_RUNNING)) {
            if (current_pid && process_get(current_pid) && process_get(current_pid)->state == PROC_RUNNING) process_get(current_pid)->state = PROC_READY;
            current_pid = candidate;
            process->state = PROC_RUNNING;
            process->ticks++;
            if (running_pid) *running_pid = current_pid;
            return AST_OK;
        }
    }
    return AST_ERR_NOT_FOUND;
}

ast_status_t scheduler_block(uint32_t pid) {
    process_t *process = process_get(pid);
    if (!process) return AST_ERR_NOT_FOUND;
    process->state = PROC_BLOCKED;
    if (current_pid == pid) current_pid = 0;
    return AST_OK;
}

ast_status_t scheduler_unblock(uint32_t pid) {
    process_t *process = process_get(pid);
    if (!process || process->state != PROC_BLOCKED) return AST_ERR_NOT_FOUND;
    process->state = PROC_READY;
    return AST_OK;
}
