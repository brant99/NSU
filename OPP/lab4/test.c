#include <math.h>
#include <mpi.h>
#include <stdlib.h>
#include <stdio.h>
#define e 1e-10
#define a 1e+5
int main(int argc,char *argv[]){
	double beg[3]={-1,-1,-1};
	double D[3]={1,1,1};
	int N[3]={30,30,30};
	double *phi_m;
	double h[3];
	int i,j,k,m;
	int dims[3]={1,1,1};
  int periods[3]={0,0,0},cords[3];
	int process_id,amount_proc;
	int size[3]={(N[0]/dims[0]+2),(N[1]/dims[1]+2),(N[2]/dims[2])+2};
	double* borders[2][6];
	int check[6]={1,1,1,1,1,1};
	MPI_Comm mesh_comm;
	int verify=1;
	double start,end;
  MPI_Init(&argc,&argv);
  MPI_Comm_size(MPI_COMM_WORLD,&amount_proc);
  MPI_Comm_rank( MPI_COMM_WORLD, &process_id );
  MPI_Cart_create(MPI_COMM_WORLD, 3, dims, periods, 0, &mesh_comm);
  MPI_Cart_coords(mesh_comm, process_id, 3, cords);

	for(i=0;i<3;i++){
		h[i]=fabs(beg[i]-D[i])/(N[i]-1);
		if(!cords[i] || cords[i]==dims[i]-1){
			if(!cords[i])
				check[i]=0;
			else
				check[i+3]=0;
			size[i]--;
			if(dims[i]-1==0){
				check[i+3]=0;
				size[i]--;
			}
		}
  }
  //printf("%i,%i,%i %i\n",cords[0],cords[1],cords[2],process_id);
     printf("%i %i %i %i %i %i\n" ,check[0],check[1],check[2],check[3],check[4],check[5]);
  MPI_Comm_free(&mesh_comm);
  MPI_Finalize();
}
