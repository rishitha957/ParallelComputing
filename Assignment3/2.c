#include <stdio.h>
#include "mpi.h" 
#include <stdlib.h>  

int main(int argc, char* argv[])
{
    int np, rank;
    int n = atoi(argv[1]);
    MPI_Status status;
    MPI_Init(&argc, &argv);                                
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &np); 
    if(rank==0){
        int a_1[n],a[n];
        srand(rank);
        for(int j=0;j<n;j++){
            a[j] = rand()%10;
        }   
        MPI_Send(&a[0], n, MPI_INT, 1, 0, MPI_COMM_WORLD);
        printf("rank %d sent data to rank %d\n",rank,rank+1);
        MPI_Recv(&a_1, n, MPI_INT, np-1, 0, MPI_COMM_WORLD, &status);
        printf("rank %d received data from rank %d\n",rank,np-1);
    }
    else{
        int a[n],a_1[n];
        MPI_Recv(&a, n, MPI_INT, rank-1, 0, MPI_COMM_WORLD, &status);
        printf("rank %d received data from rank %d\n",rank,rank-1);
        srand(rank);
        for(int j=0;j<n;j++){
            a_1[j] = rand()%10;
        }
        MPI_Send(&a_1[0], n, MPI_INT, (rank+1)%np, 0, MPI_COMM_WORLD);
        printf("rank %d sent data to rank %d\n",rank,(rank+1)%np);
    }
    MPI_Finalize();                                
    return 0;
}