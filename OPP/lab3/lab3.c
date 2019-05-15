#include<mpi.h>
#include<math.h>
#include<stdio.h>
#include <stdlib.h>

void mult(double*result,double*mat1,double *mat2,size_t l1, size_t h1,size_t l2){
    size_t i,j,k;
    for(j=0;j<h1;j++)
      for(i=0;i<l1;i++)
        for(k=0;k<l2;k++)
          result[k+j*l2]+=mat1[j*l1+i]*mat2[k+i*l2];
}

int main(int argc,char *argv[]){
    double *a,*b,*c;
    double *subA,*subB,*subC;
    double start,end;
    int amount_proc,process_id;
    int p1=4,p2=2;
    size_t i;
    size_t n1=1600,n2=1600,n3=400;
    int dims[2]={p1,p2};
    int periods[2]={0,0},cords[2];
    MPI_Comm mesh_comm;
    MPI_Comm row_comm, col_comm;
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&amount_proc);
    MPI_Comm_rank( MPI_COMM_WORLD, &process_id );
    MPI_Cart_create(MPI_COMM_WORLD, 2, dims, periods, 0, &mesh_comm);
    MPI_Cart_coords(mesh_comm, process_id, 2, cords);
    MPI_Comm_split(mesh_comm, cords[0],cords[1] , &row_comm);
    MPI_Comm_split(mesh_comm, cords[1],cords[0] , &col_comm);
    subA = (double*)malloc(n1 / dims[0] * n2 * sizeof(double));
    subB = (double*)malloc( n3/dims[1] * n2 * sizeof(double));
    subC = (double*)calloc(n1 / dims[0]*n3/dims[1] , sizeof(double));
    if (process_id == 0) {
        a = (double *) malloc(n1 * n2 * sizeof(double));
        b = (double *) malloc(n2 * n3 * sizeof(double));
        c = (double *) calloc(n1 * n3 , sizeof(double));
        for (int i = 0; i < n1; ++i) {
            for (int j = 0; j < n2; ++j) {
                a[n2 * i + j] = 1;
            }
        }
        for (int i = 0; i < n3; ++i) {
            for (int j = 0; j < n2; ++j) {
                b[n2 * i + j] = 2;
            }
        }
    }
    start=MPI_Wtime();
    if(!cords[1])
    	MPI_Scatter(a,n1 / dims[0] * n2 , MPI_DOUBLE, subA, n1 / dims[0] * n2, MPI_DOUBLE, 0, col_comm);
    if(!cords[0])
    	MPI_Scatter(b, n3/dims[1] * n2, MPI_DOUBLE, subB, n3/dims[1] * n2, MPI_DOUBLE, 0, row_comm);
    MPI_Bcast(subA, n1 / dims[0] * n2, MPI_DOUBLE, 0, row_comm);
    MPI_Bcast(subB, n3/dims[1] * n2, MPI_DOUBLE, 0, col_comm);
    mult(subC,subA,subB,n2,n1 / dims[0],n3/dims[1]);
    if(process_id)
    	MPI_Send(subC,n1 / dims[0] *n3/dims[1] , MPI_DOUBLE, 0,0, mesh_comm);
    else{	
      size_t i1,j1;
      size_t j;
      for(i=0;i<dims[0];i++){
        for(j=0;j<dims[1];j++){
          if(i || j)
            MPI_Recv(subC, n1 / dims[0] *n3/dims[1], MPI_DOUBLE, i*dims[1]+j, 0, mesh_comm, MPI_STATUS_IGNORE);
          for(i1=0;i1<n1 / dims[0];i1++){
            for (j1 = 0; j1 < n3/dims[1]; j1++) {
                c[i*n1 / dims[0]*n3+j*n3/dims[1]+i1*n3+j1]=subC[i1*n3/dims[1] +j1];
            }
          }
        }
      }
      end=MPI_Wtime();
      free(a);
      free(b);
      free(c);
    printf("mesh %i*%i\nn1=%li n2=%li n3=%li\n%f sec",p1,p2,n1,n2,n3,end-start);
    }
    free(subA);
    free(subB);
    free(subC);
    MPI_Comm_free(&col_comm);
    MPI_Comm_free(&row_comm);
    MPI_Comm_free(&mesh_comm);
    MPI_Finalize();
    return 0;
}
