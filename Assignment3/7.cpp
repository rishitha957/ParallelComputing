#include<bits/stdc++.h>
#include "mpi.h"
#include <omp.h>

using namespace std;

int main(int argc, char **argv){
    int rank,np;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &np);
    int n= atoi(argv[1]);
    int a[n];
    int n_each = n/np;
    if(rank==0){
        srand(time(NULL));
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
        #pragma omp parallel for reduction(+: sum)
        for(int i=0;i<n_each;i++)
        {
            sum+=a[i];
        }
        int temp_sum = 0;
        for(int i=1;i<np;i++)
        {
            MPI_Recv(&temp_sum,1,MPI_INT,MPI_ANY_SOURCE,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
            sum+=temp_sum;
        }
        cout<<"total sum - "<<sum<<endl;
    }
    else{
        MPI_Recv(&n_each,1,MPI_INT,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        int a1[n_each];
        MPI_Recv(&a1,n_each,MPI_INT,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        int temp_sum=0;
        #pragma omp parallel for reduction(+: temp_sum)
        for(int i=0;i<n_each;i++)
        {
            temp_sum+=a1[i];
        }
        MPI_Send(&temp_sum,1,MPI_INT,0,0,MPI_COMM_WORLD);
    }
    MPI_Finalize();
}