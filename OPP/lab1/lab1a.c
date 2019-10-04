#include<mpi.h>
#include<math.h>
#include<stdio.h>
#include <stdlib.h>

void mult(double*result,double*mat1,double *mat2,size_t sizeStr, int sizeCol){
    int i=0;
    for(;i<sizeCol;i++)
      result[i]=0;
    for(i=0;i<sizeCol*sizeStr;i++)
        result[i/sizeStr]+=(mat1[i]*mat2[i%sizeStr]);
}

int main(int argc,char *argv[]){
    MPI_Init(&argc,&argv);
    double *b,*x,*y,*a,*u,*piece,data[2],T[2],epsilon=pow(10,-10),t,t1,t2;
    int i,amount_proc,n=30000,sizeCol,shiftCol,recSize,shRecCol;
    int process_id;
    MPI_Comm_size(MPI_COMM_WORLD,&amount_proc);
    MPI_Comm_rank( MPI_COMM_WORLD, &process_id );
    if(n%amount_proc>process_id){
      sizeCol=n/amount_proc+1;
      shiftCol=sizeCol*process_id;
    }
    else {
      sizeCol=n/amount_proc;
      shiftCol=(sizeCol+1)*(n%amount_proc)+(process_id-n%amount_proc)*sizeCol;
    }
    u=calloc(n,sizeof(double));
    b=calloc(n,sizeof(double));
    x=calloc(n,sizeof(double));
    a=calloc(n*sizeCol,sizeof(double));
    y=calloc(n,sizeof(double));
    piece=calloc(n,sizeof(double));
    if(process_id==0)
      t1=MPI_Wtime();
    for(i=0;i<n*sizeCol;i++){
      if(!(i%sizeCol)){
        u[i/sizeCol]=sin((2*pow(M_PI,2)*(i/sizeCol))/(180*n));;
      }
      if(i/n+shiftCol==i%n)
        a[i]=2;
      else
        a[i]=1;
    }
    mult(&b[shiftCol],a,u,n,sizeCol);

    do{
      mult(piece,a,x,n,sizeCol);
      for(i=0;i<sizeCol;i++){
        piece[i]-=b[shiftCol+i];
      }
      recSize=n/amount_proc+1;
      shRecCol=0;
      for(i=0;i<amount_proc;i++){
        if(n%amount_proc==i)
          recSize--;
        MPI_Sendrecv(piece,sizeCol,MPI_DOUBLE,i,process_id,&y[shRecCol],recSize,MPI_DOUBLE,i,i,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        shRecCol+=recSize;
      }
      mult(piece,a,y,n,sizeCol);
      mult(&data[0],&y[shiftCol],piece,sizeCol,1);
      mult(&data[1],piece,piece,sizeCol,1);
      MPI_Allreduce(&data,&T,2,MPI_DOUBLE,MPI_SUM,MPI_COMM_WORLD);
      t=T[0]/T[1];
      for(i=0;i<n;i++)
        x[i]-=t*y[i];
      for(i=0;i<sizeCol;i++){
        data[0]=pow(y[i],2);
        data[1]=pow(b[i],2);
      }
      MPI_Allreduce(&data,&T,2,MPI_DOUBLE,MPI_SUM,MPI_COMM_WORLD);
    }while(sqrt(T[0]/T[1])>=epsilon);
    if(process_id==0){
      t2=MPI_Wtime();
      printf("takes %f time\n",t2-t1 );
    }
    free(a);
    free(b);
    free(x);
    free(y);
    free(u);
    free(piece);
    MPI_Finalize();
    return 0;
}
