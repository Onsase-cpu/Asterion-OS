#include "asterion.h"
#include <stdio.h>
#include <string.h>
void shell_help(void){puts("help  ps  mem  mounts  uname  clear  exit");}
void shell_ps(void){printf("PID  STATE    PRIORITY  NAME\n");for(uint32_t i=1;i<=ASTERION_MAX_PROCESSES;i++){process_t *p=process_get(i);if(p)printf("%-4u %-8d %-9u %s\n",p->pid,p->state,p->priority,p->name);}}
void shell_uname(void){printf("%s %s x86_64\n",ASTERION_NAME,ASTERION_VERSION);}
