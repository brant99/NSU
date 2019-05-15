#include <stdio.h>
#include <stdlib.h>
#define N 30
int main(){
  double epsilon=0.001;
  double value=0,preval=0;
  double x=epsilon;
  double *data;
  double tmp;

  data=malloc(sizeof(double)*N);
  for(int i=0;i<N;i++)
   scanf("%lf",&data[i]);
  while(x<=1){
    for(int i=0;i<N;i++){
      if(x-data[i]>=0)
        value++;
    }
    value/=N;
    if(preval!=value)
      printf("%lf %lf\n%lf %lf\n",x,preval,x,value);
    preval=value;
    value=0;
    x+=epsilon;
  }
  return 0;
}
