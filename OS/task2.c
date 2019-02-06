#include <stdio.h>
#include <time.h>
int main(){
  struct tm* date;
  time_t rawtime;
  time(&rawtime);
  date=gmtime(&rawtime);
  date->tm_hour-=8;
  mktime(date);
  printf("%s\n",asctime(date) );
}
