#include <stdio.h>
#include "mpi.h" 
#include <stdlib.h>  

int main(int argc, char* argv[])
{
    int np, rank;
    int n = atoi(argv[1]);
    int n_each = n/np, n_recv;
    int a[n];
    int temp_res[n_each];
    MPI_Status status;
    MPI_Init(&argc, &argv);                                
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &np);  
    if(rank == 0){
        for(int i=0;i<n;i++){
            a[i] = rand()%10;
        }
        if(np>1){
            for(int i=1;i<np-1;i++){
                MPI_Send( &n_each , 1, MPI_INT, i, 0, MPI_COMM_WORLD);
                MPI_Send( &a[i*n_each], n_each, MPI_INT, i, 0, MPI_COMM_WORLD);
            }
            int ind = (np-1)*(n_each);
            int to_send = n-ind;
            MPI_Send(&to_send, 1, MPI_INT, np-1, 0, MPI_COMM_WORLD);
            MPI_Send(&a[ind], to_send, MPI_INT, np-1, 0, MPI_COMM_WORLD);
        }
        int sum = 0;
        for(int i=0;i<n_each;i++){
            sum+=a[i];
        }
        for(int i=1;i<np;i++){
            int temp;
            MPI_Recv(&temp, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
            int sender = status.MPI_SOURCE;
            sum+=temp;
        }
        printf("Final sum: %d\n",sum);
    }
    else{
        MPI_Recv(&n_recv, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
        MPI_Recv(&temp_res, n_recv, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
        int partial_sum = 0;
        for(int i=0;i<n_recv;i++){
            partial_sum+=temp_res[i];
        }
        MPI_Send(&partial_sum, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }
    MPI_Finalize();                                
    return 0;
}