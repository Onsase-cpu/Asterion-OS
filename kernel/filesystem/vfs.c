#include "asterion.h"
#include <string.h>
static filesystem_mount_t mounts[ASTERION_MAX_MOUNTS]; static uint32_t count;
void vfs_init(void){memset(mounts,0,sizeof(mounts));count=0;}
ast_status_t vfs_mount(const char *name,const char *mountpoint,uint32_t flags){if(!name||!mountpoint||count>=ASTERION_MAX_MOUNTS)return AST_ERR_INVALID; mounts[count++]=(filesystem_mount_t){name,mountpoint,flags}; return AST_OK;}
uint32_t vfs_mount_count(void){return count;}
const filesystem_mount_t *vfs_mount_at(uint32_t index){return index<count?&mounts[index]:0;}
