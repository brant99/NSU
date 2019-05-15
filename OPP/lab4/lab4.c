#include <math.h>

#define e 1e-10
#define a 1e+5

double phi(double x,double y,double z){
	return x*x+y*y+z*z;
}

double ro(double x,double y,double z){
	return 6-a*phi(x,y,z);
}


int main(int argc,char *argv[]){
	double beg[3]={-1,-1,-1};
	double D[3]={1,1,1};
	double N[3]={30,30,30};
	double *phi_m;
	double h[3];
	int i,j,k;
	int dims[3]={2,2,2};
  int periods[3]={0,0,0},cords[3];
	int process_id,amount_proc;
	int size[3]={(N[0]/dims[0]),(N[1]/dims[1]),(N[2]/dims[2])};
	double** borders;

	MPI_Comm mesh_comm;
  MPI_Comm row_comm, col_comm;

  MPI_Init(&argc,&argv);
  MPI_Comm_size(MPI_COMM_WORLD,&amount_proc);
  MPI_Comm_rank( MPI_COMM_WORLD, &process_id );
  MPI_Cart_create(MPI_COMM_WORLD, 3, dims, periods, 0, &mesh_comm);
  MPI_Cart_coords(mesh_comm, process_id, 3, cords);
	int amount_borders=6;

	for(i=0;i<3;i++){
		h[i]=(fabs(beg[i])+fabs(D[i]))/(N[i]-1);
		/*if(!cords[i] || cords[i]==dims[i]-1){
			amount_borders--;
			if(dims[i]-1==0)
				amount_borders--;
		}*/
	}

	borders=calloc(amount_borders,sizeof(double*));

	for (i = 0; i < amount_borders; i++) {
			borders[i]=calloc(size[i%3]*size[(i+1)%3],sizeof(double));
	}

	phi_m=calloc(size[0]*size[1]*size[2],sizeof(double));

	for(k=0;k<size[0];k++)
		for(j=0;j<size[1];j++)
			for(i=0;i<size[2];i++)
				if(!k && !cords[0] ||!j && !cords[1] || !i && !cords[2] ||
					cords[0]==dims[0]-1 && k==size[2]-1|| cords[1]==dims[1]-1 && j==size[1]-1|| cords[2]==dims[2]-1 && i==size[0]-1)
					phi[i+j*size[0]+k*size[0]*size[1]]=phi(beg[2]+(i+cords[2]*size[2])*h[2],beg[1]+(j+cords[1]*size[1])*h[1],beg[0]+(k+cords[0]*size[0])*h[0]);

	double param=(1/(2/(h[0]*h[0])+2/(h[1]*h[1])+2/(h[2]*h[2])+a));
	MPI_Request reqR,reqS;

	for (k = 0; k < 2; k++) {
		for(j=0;j<size[1];j++){
			if(!cords[0] && !k || cords[0]==dims[0]-1 && k==1)
				break;
			for(i=0;i<size[2];i++){
					borders[k][i+j*size[2]]=phi[i+1]
			}
		}
	}
		for (i = 1; i < size[0]-1; i++) {
			/*
			phi_m[i+size[0]*j+size[0]*size[1]]=param*((phi_m[i+1+j*size[0]+size[0]*size[1]]-phi_m[i-1+j*size[0]+size[0]*size[1]])/h[0]*h[0]+
			(phi_m[i+(j+1)*size[0]+size[0]*size[1]]-phi_m[i+(j-1)*size[0]+size[0]*size[1]])/h[1]*h[1]+
			(phi_m[i+j*size[0]+2*size[0]*size[1]]-phi_m[i+j*size[0]])/h[2]*h[2]);
				MPI_Irecv(&phi_m[i+size[0]*j],1,MPI_DOUBLE,(cords[0]-1)*dims[1]*dims[2]+cords[1]*dims[2]+cords[2],i+size[0]*j,mesh_comm,MPI_STATUS_IGNORE);
				MPI_Send(&phi_m[i+size[0]*j],1,MPI_DOUBLE,);*/
		}
	}

	for(i=1;i<N[2]/dims[2];i++)
		for(j=1;j<N[1]/dims[1];j++)
			for(k=1;k<N[0]/dims[0];k++){
				phi_m[k+j*N[0]+i*N[1]*N[0]]=param*(phi_m[k+1+j*N[0]+i*N[1]*N[0]]/(h[0]*h[0])+phi_m[k+(j+1)*N[0]+i*N[1]*N[0]]/(h[1]*h[1])+phi_m[k+j*N[0]+(i+1)*N[1]*N[0]]/(h[2]*h[2])
				-ro((cords[0]*N[0]/dims[0]+(i-1))*h[0],(cords[1]*N[1]/dims[1]+(j-1))*h[1],(cords[2]*N[2]/dims[2]+(k-1))*h[2]));
			}



}
