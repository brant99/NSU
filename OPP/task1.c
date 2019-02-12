#include<mpi.h>
#include<math.h>
#include<stdio.h>
#include <stdlib.h>

double mult(double *a,double *x,int n){
    int i=0;
    double result=0;
    for(;i<n;i++)
        result+=(a[i]*x[i]);
    return result;
}

int main(int argc,char *argv[]){
    MPI_Init(&argc,&argv);
    double *b,*x,*y,*a,*u,data[2],T[2],epsilon=pow(10,-5),t,argument;
    int i,amount_proc,n=6,partN,begnum;
    int process_id;
    MPI_Comm_size(MPI_COMM_WORLD,&amount_proc);
    MPI_Comm_rank( MPI_COMM_WORLD, &process_id );
    if((n*n)%amount_proc>process_id){
      partN=(n*n)/amount_proc+1;
      begnum=partN*process_id;
      argument=(2*pow(M_PI,2)*(begnum%n))/(180*n);
    }
    else {
      partN=(n*n)/amount_proc;
      begnum=(n*n)%amount_proc*(partN+1)+(process_id-(n*n)%amount_proc)*partN;
      argument=(2*pow(M_PI,2)*(begnum%n))/(180*n);
    }
    u=malloc(sizeof(double)*partN);
    b=malloc(sizeof(double)*n);
    x=malloc(sizeof(double)*n);
    a=malloc(sizeof(double)*partN);
    y=malloc(sizeof(double)*n);
    for(i=0;i<partN;i++){
          u[i]=sin(argument+2*pow(M_PI,2)*i/(180.0*n));
        x[i]=0;
        if((begnum+i)%n==(begnum+i)/n)
          a[i]=2;
        else
          a[i]=1;
    }
    int piece=partN;
    int begtmp=begnum;
    while(piece+begtmp%n=>n){
      b[begtmp/n]=mult(&a[begtmp%n-begnum%n],&u[begtmp%n-begnum%n],n-begtmp%n);
      y[begtmp/n]=mult(&a[begtmp%n-begnum%n],&x[begtmp%n],n-begtmp%n);
      y[begtmp/n]-=b[begtmp/n];
      piece-=n-begtmp%n;
      begtmp+=n-begtmp%n;
    }
    b[begtmp/n]=mult(&a[begtmp%n-begnum%n],&u[begtmp%n-begnum%n],piece);
    y[begtmp/n]=mult(&a[begtmp%n-begnum%n],&x[begtmp%n],piece);
    y[begtmp/n]-=b[begtmp/n];
    for(i=0;i<n;i++)
      if(i<begnum/n && i>begtmp/n)
        b[i]=0;
    MPI_Allreduce(b,b,n,MPI_DOUBLE,MPI_SUM,MPI_COMM_WORLD);
    while(sqrt(T[0]/T[1])>=epsilon){
      piece=partN;
      begtmp=begnum;
      while(piece+begtmp%n=>n){

        piece-=n-begtmp%n;
        begtmp+=n-begtmp%n;
      }

        for(i=0;i<n;i++)
          if(i<begnum/n && i>begtmp/n)
            y[i]=0;
        MPI_Allreduce(y,y,n,MPI_DOUBLE,MPI_SUM,MPI_COMM_WORLD);
//think about it!!!!!!!!!!!!
        data[0]=mult(&a[begtmp%n-begn],&y[begtmp/n],partN);
        data[1]=data[0]*data[0];
        data[0]*=y[process_id];
        MPI_Allreduce(&data,&T,2,MPI_DOUBLE,MPI_SUM,MPI_COMM_WORLD);
        t=T[0]/T[1];
        for(i=0;i<n;i++)
            x[i]=x[i]-t*y[i];
        printf("|%f|  \n",data[0]/y[process_id]-b[process_id]-y[process_id]);
        data[0]=pow(data[0]/y[process_id],2);
        data[1]=pow(b[process_id],2);
        MPI_Allreduce(&data,&T,2,MPI_DOUBLE,MPI_SUM,MPI_COMM_WORLD);
        if(process_id==0)
          printf("\n");
    }
    free(a);
    free(b);
    free(x);
    free(y);
    MPI_Finalize();
    return 0;
}
