#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
int main(int argc,char** argv){
	int f=open(argv[1],O_WRONLY);
	char s[BUFSIZ];
	while(fgets(s,BUFSIZ,stdin))
	write(f,s,4);
       close(f);	
}
