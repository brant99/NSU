#include<mpi.h>
#include<math.h>
#include<stdio.h>
#include <stdlib.h>
int main(int argc,char *argv[]){
    int amount_proc,process_id,cur_cell;
    int p1=2,p2=4;
    size_t i;
    size_t n1=8,n2=8,n3=8;
    int dims[2]={p1,p2};
    int a[16]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
    int aa[4]={0,0,0,0};
    int periods[2]={0,0},cords[2];
    MPI_Comm mesh_comm;
    MPI_Comm row_comm, col_comm;
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&amount_proc);
    MPI_Comm_rank( MPI_COMM_WORLD, &process_id );
    MPI_Cart_create(MPI_COMM_WORLD, 2, dims, periods, 0, &mesh_comm);
    MPI_Comm_rank( mesh_comm, &cur_cell );
    MPI_Cart_coords(mesh_comm, cur_cell, 2, cords);
    MPI_Comm_split(mesh_comm, process_id/(cords[1]+1), process_id, &row_comm);
    MPI_Comm_split(mesh_comm, cords[1], cords[0], &col_comm);
    //if(!process_id)
    MPI_Scatter(a,4 , MPI_INT, aa, 4, MPI_INT, 0, MPI_COMM_WORLD);
   if(process_id==4)
    for(int i=0;i<4;i++)
      printf("%i ",aa[i] );
      //printf("%i %i %i\n",process_id,cords[0],cords[1] );
      MPI_Finalize();
  }
