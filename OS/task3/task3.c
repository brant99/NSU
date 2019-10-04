#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <ulimit.h>
#include <sys/time.h>
#include <sys/resource.h>
extern char **environ;
int main(int argc, char *argv[]){
  int opt,invalid=0,i=0;
  struct rlimit rlim;
  rlim_t size;
  char* value=NULL,*name=NULL,options[ ] = "ispucdvU:C:V:";
  printf("arg equals %d\n",argc);
  printf("Ruid=%u\nEuid=%u\n",getuid(),geteuid());
  return 0;
}
