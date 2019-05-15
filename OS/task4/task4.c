#define List struct list
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

List{
  char* str;
  List *next;
};

void newVert(List* text,char *stroke,size_t size){
  List*tmp=text;
  while(tmp)
    tmp=tmp->next;
  tmp=malloc(sizeof(List));
  tmp->str=malloc(sizeof(char)*size);
  for(;size>0;size--)
    tmp->str[size]=stroke[size];
  tmp->next=NULL;
}

int main(){
  char tmp[100];
  List *text=NULL;
  gets(tmp);
  while(tmp[0]!='.'){
    newVert(text,tmp,strlen(tmp));
    gets(tmp);
  }
  for(;text;text=text->next){
    printf("%s\n",text->str );
  }
  return 0;
}
