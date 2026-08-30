#include "asterion.h"
#include <assert.h>
#include <stdio.h>
int main(void){page_allocator_t m;page_allocator_init(&m,4*ASTERION_PAGE_SIZE);assert(m.total_pages==4);assert(page_alloc(&m,2)==AST_OK);assert(page_free(&m,1)==AST_OK);process_table_init();uint32_t a,b,r;assert(process_create("alpha",1,&a)==AST_OK);assert(process_create("beta",1,&b)==AST_OK);scheduler_init();assert(scheduler_tick(&r)==AST_OK);assert(r==a);assert(scheduler_tick(&r)==AST_OK);assert(r==b);vfs_init();assert(vfs_mount("astfs","/",0)==AST_OK);assert(vfs_mount_count()==1);puts("Asterion tests: PASS");return 0;}
