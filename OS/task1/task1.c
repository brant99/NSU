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
        setpgid(getpid(),getpgid(getpid()));
      case 'p':
        printf("PID=%u\nPPID=%u\nPGID=%u\n", getpid(),getppid(),getpgid(getpid()));
        break;
      case 'c':
        getrlimit(RLIMIT_CORE,&rlim);
        printf("LIM_Core_soft=%lu LIM_Core_hard=%lu\n",rlim.rlim_cur,rlim.rlim_max);
        break;
      case 'C':
        size=atol(optarg);
        rlim.rlim_cur=0;
        rlim.rlim_max=size;
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
        for(i=0;optarg[i]!='=';i++){}
        value=&optarg[i+1];
        name=malloc(sizeof(char)*i);
        for(i=0;optarg[i]!='=';i++){
          name[i]=optarg[i];
        }
        setenv(name,value,1);
        value=NULL;
        free(name);
        break;
      case '?':
        printf("Unknown Option %d\n",optind);
        invalid++;
    }
  }
  printf("invalid equals %d\n",invalid);
  return 0;
}
