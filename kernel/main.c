#include "asterion.h"
#ifdef HOSTED
#include <stdio.h>
void console_write(const char *m){fputs(m,stdout);}
void console_write_line(const char *m){printf("%s\n",m);}
void kernel_panic(const char *r){fprintf(stderr,"ASTERION PANIC: %s\n",r);}
#else
void console_write(const char *m){(void)m;} void console_write_line(const char *m){(void)m;} void kernel_panic(const char *r){(void)r; for(;;){__asm__ volatile("hlt");}}
#endif
void kernel_main(void){page_allocator_t memory;uint32_t pid; page_allocator_init(&memory,128ull*1024*1024);process_table_init();scheduler_init();vfs_init();astfs_init();syscall_init();process_create("init",10,&pid);console_write_line("Asterion OS kernel foundation online");}
