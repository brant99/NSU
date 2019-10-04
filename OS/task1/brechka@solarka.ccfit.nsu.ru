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
  while((opt=getopt(argc,argv,options))!=EOF){
    switch (opt) {
      case 'i':
        printf("Ruid=%u\nEuid=%u\nRGid=%u\nEgid=%u\n",getuid(),geteuid(),getgid(),getegid());
        break;
      case 'u':
        printf("ulimit=%ld\n",ulimit(UL_GETFSIZE));
        break;
      case 'U':
        ulimit(UL_SETFSIZE,atol(optarg));
        break;
      case 's':
        setpgid(getpid(),0);
      case 'p':
        printf("PID=%u\nPPID=%u\nPGID=%u\n", getpid(),getppid(),getpgid();
        break;
      case 'c':
        getrlimit(RLIMIT_CORE,&rlim);
        printf("LIM_Core_soft=%lu LIM_Core_hard=%lu\n",rlim.rlim_cur,rlim.rlim_max);
        break;
      case 'C':
        size=atol(optarg);
        rlim.rlim_cur=size;
        setrlimit(RLIMIT_CORE,&rlim);
        break;
      case 'd':
        printf("%s\n",getcwd(NULL,0));
        break;
      case 'v':
        while(*environ)
          printf("%s\n",*environ++ );
        break;
      case 'V':
        putenv(optarg);
        break;
      case '?':
        printf("Unknown Option %d\n",optind);
        invalid++;
    }
  }
  printf("invalid equals %d\n",invalid);
  return 0;
}
