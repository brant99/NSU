#include <mpi.h>
#include <stdio.h>
int main(int argc,char *argv[]){

MPI_Comm mesh_comm;
MPI_Comm row_comm, col_comm;

MPI_Init(&argc,&argv);
double beg[3]={-1,-1,-1};
double D[3]={1,1,1};
double N[3]={30,30,30};
double *phi_m;
double h[3];
int i,j,k;
int dims[3]={2,2,1};
int periods[3]={0,0,0},cords[3];
int process_id,amount_proc;
int size[3]={(N[0]/dims[0]+2),(N[1]/dims[1]+2),(N[2]/dims[2]+2)};
int source ,dest,d;
MPI_Comm_size(MPI_COMM_WORLD,&amount_proc);
MPI_Comm_rank( MPI_COMM_WORLD, &process_id );
MPI_Cart_create(MPI_COMM_WORLD, 3, dims, periods, 0, &mesh_comm);
MPI_Cart_coords(mesh_comm, process_id, 3, cords);
MPI_Cart_shift(mesh_comm,0,1,&source,&dest);
printf("%d,%d,%d %d    %d %d\n",cords[0],cords[1],cords[2],process_id ,source,dest );
}
