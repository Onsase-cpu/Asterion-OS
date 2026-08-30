#include "asterion.h"
#include <string.h>

static process_t table[ASTERION_MAX_PROCESSES];
static uint32_t next_pid = 1;

void process_table_init(void) {
    memset(table, 0, sizeof(table));
    next_pid = 1;
}

ast_status_t process_create(const char *name, uint8_t priority, uint32_t *pid_out) {
    if (!name || !pid_out || priority == 0) return AST_ERR_INVALID;
    for (uint32_t i = 0; i < ASTERION_MAX_PROCESSES; ++i) {
        if (table[i].state == PROC_UNUSED) {
            table[i].pid = next_pid++;
            strncpy(table[i].name, name, sizeof(table[i].name) - 1);
            table[i].name[sizeof(table[i].name) - 1] = '\0';
            table[i].priority = priority;
            table[i].state = PROC_READY;
            table[i].ticks = 0;
            *pid_out = table[i].pid;
            return AST_OK;
        }
    }
    return AST_ERR_FULL;
}

process_t *process_get(uint32_t pid) {
    for (uint32_t i = 0; i < ASTERION_MAX_PROCESSES; ++i) if (table[i].state != PROC_UNUSED && table[i].pid == pid) return &table[i];
    return NULL;
}

uint32_t process_count(void) {
    uint32_t count = 0;
    for (uint32_t i = 0; i < ASTERION_MAX_PROCESSES; ++i) if (table[i].state != PROC_UNUSED) ++count;
    return count;
}
