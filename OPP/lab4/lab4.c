#include <math.h>
#include <mpi.h>
#include <stdlib.h>
#include <stdio.h>
#define e 1e-8
#define a 1e5

double phi(double x,double y,double z){
	return x*x+y*y+z*z;
}

double ro(double x,double y,double z){
	return 6-a*phi(x,y,z);
}
int phi_inside(int i,int j,int k,double *phi_m,int *cords,double *beg,double* h,int *size,double param,int *check,int ver){
	double prevPhi=phi_m[i+j*size[2]+k*size[2]*size[1]];
	phi_m[i+j*size[2]+k*size[2]*size[1]]=param*
	((phi_m[i+1+j*size[2]+k*size[2]*size[1]]-phi_m[i-1+j*size[2]+k*size[2]*size[1]])/(h[2]*h[2])+
	(phi_m[i+(j+1)*size[2]+k*size[2]*size[1]]-phi_m[i+(j-1)*size[2]+k*size[2]*size[1]])/(h[1]*h[1])+
	(phi_m[i+j*size[2]+(k+1)*size[2]*size[1]]-phi_m[i+j*size[2]+(k-1)*size[2]*size[1]])/(h[0]*h[0])-
	ro(beg[2]+(i-check[2]+cords[2]*(size[2]-check[2]-check[5]))*h[2],
		beg[1]+(j-check[1]+cords[1]*(size[1]-check[1]-check[4]))*h[1],
		beg[0]+(k-check[0] +cords[0]*(size[0]-check[0]-check[3]))*h[0]));
	if(ver==1|| fabs(prevPhi-phi_m[i+j*size[2]+k*size[2]*size[1]])>=e)
		return 1;
	else
	 return 0;
}

int main(int argc,char *argv[]){
	double beg[3]={-1,-1,-1};
	double D[3]={1,1,1};
	int N[3]={300,500,400};
	double *phi_m;
	double h[3];
	int i,j,k,m;
	int dims[3]={1,1,2};
  int periods[3]={0,0,0},cords[3];
	int process_id,amount_proc;
	int size[3]={(N[0]/dims[0]+2),(N[1]/dims[1]+2),(N[2]/dims[2])+2};
	double* borders[2][6];
	int check[6]={1,1,1,1,1,1};
	MPI_Comm mesh_comm;
	int verify=1;
	int tmp;
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

	for (i = 0; i < 3; i++) {
		if(check[i]){
			borders[0][i]=calloc((size[(i+2)%3]-2)*(size[(i+1)%3]-2),sizeof(double));
			borders[1][i]=calloc((size[(i+2)%3]-2)*(size[(i+1)%3]-2),sizeof(double));
		}
		if(check[i+3]){
			borders[0][i+3]=calloc((size[(i+2)%3]-2)*(size[(i+1)%3]-2),sizeof(double));
			borders[1][i+3]=calloc((size[(i+2)%3]-2)*(size[(i+1)%3]-2),sizeof(double));
		}
	}
	phi_m=calloc(size[0]*size[1]*size[2],sizeof(double));

	for(k=check[0];k<size[0]-check[3];k++)
		for(j=check[1];j<size[1]-check[4];j++)
			for(i=check[2];i<size[2]-check[5];i++)
				if(!k	 && !cords[0] ||!j && !cords[1] || !i && !cords[2] ||
					cords[0]==dims[0]-1 && k==size[0]-1-check[3]|| cords[1]==dims[1]-1 && j==size[1]-check[4]-1|| cords[2]==dims[2]-1 && i==size[2]-1-check[5])
					phi_m[i+j*size[2]+k*size[2]*size[1]]=phi(beg[2]+(i-check[2]+cords[2]*(size[2]-check[2]-check[5]))*h[2],beg[1]+(j-check[1]+cords[1]*(size[1]-check[1]-check[4]))*h[1],beg[0]+(k-check[0]+cords[0]*(size[0]-check[0]-check[3]))*h[0]);

	double param=1/(2/(h[0]*h[0])+2/(h[1]*h[1])+2/(h[2]*h[2])+a);
	MPI_Request reqR[6],reqS[6];
	MPI_Status st;

	if (process_id==0){
		start=MPI_Wtime();
	}
	while(verify){
		verify=0;
		if(check[0] ||check[3]){
			for(j=1;j<size[1]-1;j++){
				for(i=1;i<size[2]-1;i++){
					if(check[0]){
						verify=phi_inside(i,j,1,phi_m,cords,beg,h,size,param,check,verify);
						borders[0][0][i-1+(j-1)*(size[2]-2)]=phi_m[i+j*size[2]+size[2]*size[1]];
					}
					if(check[3]){
						verify=phi_inside(i,j,size[0]-2,phi_m,cords,beg,h,size,param,check,verify);
						borders[0][3][i-1+(j-1)*(size[2]-2)]=phi_m[i+j*size[2]+(size[0]-2)*size[2]*size[1]];
					}
				}
			}
		if(check[0]){
			MPI_Irecv(borders[1][0], (size[2]-2)*(size[1]-2), MPI_DOUBLE,
			 (cords[0]-1)*dims[1]*dims[2]+cords[1]*dims[2]+cords[2], 3, MPI_COMM_WORLD, &reqR[0]);
			MPI_Isend(borders[0][0],(size[2]-2)*(size[1]-2),MPI_DOUBLE,
			(cords[0]-1)*dims[1]*dims[2]+cords[1]*dims[2]+cords[2],0,MPI_COMM_WORLD,&reqS[0]);
		}
		if(check[3]){
			MPI_Irecv(borders[1][3], (size[2]-2)*(size[1]-2), MPI_DOUBLE,
			 (cords[0]+1)*dims[1]*dims[2]+cords[1]*dims[2]+cords[2], 0, MPI_COMM_WORLD, &reqR[3]);
			MPI_Isend(borders[0][3],(size[2]-2)*(size[1]-2),MPI_DOUBLE,
			(cords[0]+1)*dims[1]*dims[2]+cords[1]*dims[2]+cords[2],3,MPI_COMM_WORLD,&reqS[3]);
		}
	}
		if(check[1] ||check[4]){
			for(j=1;j<size[0]-1;j++){
				for(i=1;i<size[2]-1;i++){
					if(check[1]){
						verify=phi_inside(i,1,j,phi_m,cords,beg,h,size,param,check,verify);
						borders[0][1][i-1+(j-1)*(size[2]-2)]=phi_m[i+size[2]+j*size[2]*size[1]];
					}
					if(check[4]){
						verify=phi_inside(i,size[1]-2,j,phi_m,cords,beg,h,size,param,check,verify);
						borders[0][4][i-1+(j-1)*(size[2]-2)]=phi_m[i+(size[1]-2)*size[2]+j*size[2]*size[1]];
					}
				}
			}
			if(check[1]){
				MPI_Irecv(borders[1][1],(size[0]-2)*(size[2]-2),MPI_DOUBLE,
				cords[0]*dims[1]*dims[2]+(cords[1]-1)*dims[2]+cords[2],4,MPI_COMM_WORLD,&reqR[1]);
				MPI_Isend(borders[0][1],(size[0]-2)*(size[2]-2),MPI_DOUBLE,
				cords[0]*dims[1]*dims[2]+(cords[1]-1)*dims[2]+cords[2],1,MPI_COMM_WORLD,&reqS[1]);
			}
			if(check[4]){
				MPI_Irecv(borders[1][4],(size[0]-2)*(size[2]-2),MPI_DOUBLE,
				cords[0]*dims[1]*dims[2]+(cords[1]+1)*dims[2]+cords[2],1,MPI_COMM_WORLD,&reqR[4]);
				MPI_Isend(borders[0][4],(size[0]-2)*(size[2]-2),MPI_DOUBLE,
				cords[0]*dims[1]*dims[2]+(1+cords[1])*dims[2]+cords[2],4,MPI_COMM_WORLD,&reqS[4]);
			}
		}
			if(check[2] ||check[5]){
				for(j=1;j<size[0]-1;j++){
					for(i=1;i<size[1]-1;i++){
						if(check[2]){
							verify=phi_inside(1,i,j,phi_m,cords,beg,h,size,param,check,verify);
							borders[0][2][i-1+(j-1)*(size[1]-2)]=phi_m[1+i*size[2]+j*size[2]*size[1]];
						}
						if(check[5]){
							verify=phi_inside(size[2]-2,i,j,phi_m,cords,beg,h,size,param,check,verify);
							borders[0][5][i-1+(j-1)*(size[1]-2)]=phi_m[(size[2]-2)+i*size[2]+j*size[2]*size[1]];

						}
				}
			}
			if(check[2]){
				MPI_Irecv(borders[1][2],(size[0]-2)*(size[1]-2),MPI_DOUBLE,
				cords[0]*dims[1]*dims[2]+cords[1]*dims[2]+cords[2]-1,5,MPI_COMM_WORLD,&reqR[2]);
				MPI_Isend(borders[0][2],(size[0]-2)*(size[1]-2),MPI_DOUBLE,
				cords[0]*dims[1]*dims[2]+cords[1]*dims[2]+cords[2]-1,2,MPI_COMM_WORLD,&reqS[2]);
			}
			if(check[5]){
				MPI_Irecv(borders[1][5],(size[0]-2)*(size[1]-2),MPI_DOUBLE,
				cords[0]*dims[1]*dims[2]+cords[1]*dims[2]+cords[2]+1,2,MPI_COMM_WORLD,&reqR[5]);
				MPI_Isend(borders[0][5],(size[0]-2)*(size[1]-2),MPI_DOUBLE,
				cords[0]*dims[1]*dims[2]+cords[1]*dims[2]+cords[2]+1,5,MPI_COMM_WORLD,&reqS[5]);
			}
		}

			for ( k = 1+check[0]; k < size[0]-1-check[3]; k++)
				for ( j = 1+check[1]; j < size[1]-1-check[4]; j++)
					for ( i = 1+check[2]; i < size[2]-1-check[5]; i++)
						verify=phi_inside(i,j,k,phi_m,cords,beg,h,size,param,check,verify);

				for(m=0;m<6;m++)
					if(check[m]){
						MPI_Wait(&reqS[m],&st);
						MPI_Wait(&reqR[m],&st);
					}
				if(check[0]){

					for(j=1;j<size[1]-1;j++)
						for(i=1;i<size[2]-1;i++)
							phi_m[i+j*size[2]]=borders[1][0][i-1+(j-1)*(size[2]-2)];
				}
				if(check[3]){
					for(j=1;j<size[1]-1;j++)
						for(i=1;i<size[2]-1;i++)
							phi_m[i+j*size[2]+size[1]*size[2]*(size[0]-1)]=borders[1][3][i-1+(j-1)*(size[2]-2)];
				}
				if(check[1]){
					for(j=1;j<size[0]-1;j++)
						for(i=1;i<size[2]-1;i++)
							phi_m[i+j*size[2]*size[1]]=borders[1][1][i-1+(j-1)*(size[2]-2)];
				}
				if(check[4]){
					for(j=1;j<size[0]-1;j++)
						for(i=1;i<size[2]-1;i++)
							phi_m[i+j*size[2]*size[1]+size[2]*(size[1]-1)]=borders[1][4][i-1+(j-1)*(size[2]-2)];
				}
				if(check[2]){
					for(j=1;j<size[0]-1;j++)
						for(i=1;i<size[1]-1;i++)
							phi_m[i*size[2]+j*size[2]*size[1]]=borders[1][2][i-1+(j-1)*(size[1]-2)];
				}
				if(check[5]){
					for(j=1;j<size[0]-1;j++)
						for(i=1;i<size[1]-1;i++)
							phi_m[i*size[2]+j*size[2]*size[1]+size[2]-1]=borders[1][5][i-1+(j-1)*(size[1]-2)];
				}

				tmp=verify;
				if(amount_proc>1){
				MPI_Allreduce(&tmp,&verify,1,MPI_INT,MPI_SUM,MPI_COMM_WORLD);
				MPI_Barrier(MPI_COMM_WORLD);
			}
			}
			/*if(!process_id)
					for(k=0;k<size[0];k++){
									for(j=0;j<size[1];j++){
											for(i=0;i<size[2];i++){
													printf("%f ",phi_m[i+j*size[2]+k*size[2]*size[1]]);
											}
											printf("\n");
									}
									printf("\n\n");

					}*/
			if(process_id==0){
				end=MPI_Wtime();
				printf("%lf",end-start);
			}
				for (i = 0; i < 3; i++) {
					if(check[i]){
						free(borders[0][i]);
						free(borders[1][i]);
					}
					if(check[i+3]){
						free(borders[0][i+3]);
						free(borders[1][i+3]);
					}
				}
				free(phi_m);
				MPI_Comm_free(&mesh_comm);
				MPI_Finalize();
}
