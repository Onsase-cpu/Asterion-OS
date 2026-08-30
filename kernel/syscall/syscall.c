#include "asterion.h"
#include <string.h>
static syscall_entry_t table[ASTERION_MAX_SYSCALLS];
void syscall_init(void){memset(table,0,sizeof(table));}
ast_status_t syscall_register(uint32_t n,const char *name,syscall_handler_t h){if(n>=ASTERION_MAX_SYSCALLS||!name||!h)return AST_ERR_INVALID;table[n]=(syscall_entry_t){n,name,h};return AST_OK;}
ast_status_t syscall_invoke(uint32_t n,uint64_t a,uint64_t b,uint64_t c,uint64_t d){if(n>=ASTERION_MAX_SYSCALLS||!table[n].handler)return AST_ERR_NOT_FOUND;return table[n].handler(a,b,c,d);}
