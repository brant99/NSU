#include<math.h>
#include<stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
void mult(double*result,double*mat,double *vec,size_t sizeStr, int sizeCol){
    int i,j;
    double k;
    #pragma omp parallel for schedule(dynamic) private(i,k,j)
    for(i=0;i<sizeCol;i++)
    {
	k=0;
	for(j=0;j<sizeStr;j++)
	{
	    k+=mat[i*sizeStr+j]*vec[j];
	}
	result[i]=k;
    }
}
int main(int argc,char *argv[]){
    double *b,*x,*y,*a,*u,*tmp,epsilon=pow(10,-12),t,k1,k2;
    double start,end;
    int i,n=15000;
    omp_set_num_threads(4);
    u=calloc(n,sizeof(double));
    b=calloc(n,sizeof(double));
    x=calloc(n,sizeof(double));
    a=calloc(n*n,sizeof(double));
    y=calloc(n,sizeof(double));
    tmp=calloc(n,sizeof(double));
    for(i=0;i<n*n;i++){
      if(!(i%n)){
        u[i/n]=sin((2*pow(M_PI,2)*(i/n))/(180*n));;
      }
      if(i/n==i%n)
        a[i]=2;
      else
        a[i]=1;
    }
    mult(b,a,u,n,n);
    start=omp_get_wtime();
    for(i=0;i<50;i++){
    //do{
      mult(y,a,x,n,n);
      #pragma omp parallel for schedule(dynamic) private(i)
      for(i=0;i<n;i++){
        y[i]-=b[i];
      }
      mult(tmp,a,y,n,n);
      mult(&k1,y,tmp,n,1);
      mult(&k2,tmp,tmp,n,1);
      t=k1/k2;
      #pragma omp parallel for schedule(dynamic) private(i)
      for(i=0;i<n;i++)
        x[i]-=t*y[i];
      k1=0;
      k2=0;
      #pragma omp parallel for schedule(dynamic) reduction(+:k1,k2) private(i)
      for(i=0;i<n;i++){
        k1+=pow(y[i],2);
        k2+=pow(b[i],2);
      }
    //}while(sqrt(k1/k2)>=epsilon);
    }
    end=omp_get_wtime();
    printf("(4;%f)\n",end-start);
    free(a);
    free(b);
    free(tmp);
    free(x);
    free(y);
    free(u);
    return 0;
}
