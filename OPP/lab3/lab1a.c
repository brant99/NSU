#include<mpi.h>
#include<math.h>
#include<stdio.h>
#include <stdlib.h>

void mult(double*result,double*mat1,double *mat2,size_t l1, size_t h1,size_t l2){
    size_t i,j,k;
    for(j=0;j<h1;j++)
      for(i=0;i<l1;i++)
        for(k=0;k<l2;j++)
          result[k+j*l2]+=mat1[j*l1+i]*mat2[k+i*l2];
}

int main(int argc,char *argv[]){
    double *a,*b,*c;
    double *subA,*subB,*subC;
    int amount_proc,process_id,cur_mesh;
    int p1,p2;
    size_t i;
    size_t n1,n2,n3;
    int dims[2]={p1,p2};
    int periods[2],cords[2];
    MPI_Comm mesh_comm;
    MPI_Comm row_comm, col_comm;
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&amount_proc);
    MPI_Comm_rank( MPI_COMM_WORLD, &process_id );
    for(i=0;i<2;i++)
      periods[i]=0;
    MPI_Cart_create(MPI_COMM_WORLD, 2, dims, periods, 0, &mesh_comm);
    MPI_Comm_rank(mesh_comm, &cur_mesh); //Функция определения номера процесса в области grid_comm
    MPI_Cart_coords(mesh_comm, cur_mesh, 2, cords);
    MPI_Comm_split(mesh_comm, cords[0], cords[1], &row_comm);
    MPI_Comm_split(mesh_comm, cords[1], cords[0], &col_comm);
    subA = (double*)malloc(n1 / dims[0] * n2 * sizeof(double));
    subB = (double*)malloc( n3/dims[1] * n2 * sizeof(double));
    subC = (double*)calloc(n1 / dims[0]*n3/dims[1] , sizeof(double));
    if (process_id == 0) {
        a = (double *) malloc(n1 * n2 * sizeof(double));
        b = (double *) malloc(n2 * n3 * sizeof(double));
        c = (double *) calloc(n1 * n3 , sizeof(double));
        for (int i = 0; i < n1; ++i) {
            for (int j = 0; j < n2; ++j) {
                a[n2 * i + j] = 3;
            }
        }
        for (int i = 0; i < n2; ++i) {
            for (int j = 0; j < n3; ++j) {
                b[n3 * i + j] = 2;
            }
        }
        MPI_Scatter(a,n1 / dims[0] * n2 , MPI_DOUBLE, subA, n1 / dims[0] * n2, MPI_DOUBLE, 0, col_comm);
        MPI_Scatter(b, n3/dims[1] * n2, MPI_DOUBLE, subB, n3/dims[1] * n2, MPI_DOUBLE, 0, row_comm);
    }
    MPI_Bcast(subA, n1 / dims[0] * n2, MPI_DOUBLE, 0, row_comm);
    MPI_Bcast(subB, n3/dims[1] * n2, MPI_DOUBLE, 0, col_comm);
    mult(subC,subA,subB,n2,n1 / dims[0],n3/dims[1]);
    MPI_Gather(subC,n1 / dims[0]*n3/dims[1],MPI_DOUBLE,c,n1 / dims[0]*n3/dims[1],MPI_DOUBLE,0,MPI_COMM_WORLD);
    MPI_Finalize();
    return 0;
}
