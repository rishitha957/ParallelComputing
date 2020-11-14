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
    int n_each = n/np;
    if(rank==np-1){
        n_each = n%np;
    }
    int a[n_each];
    for(int i=0;i<n_each;i++){
        a[i] = rank*n1+i;
    }
    MPI_Barrier(MPI_COMM_WORLD);
    int temp_sum = 0;
    for(int i=0;i<n;i++){
        temp_sum+=a[i];
    }
    int sum=0;
    MPI_Reduce( &local_sum , &sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    if(rank==0){
        printf("Total sum - %d\n",sum);
    }
    MPI_Finalize();                                
    return 0;
}