#include <stdio.h>
#include "mpi.h" 
#include <stdlib.h>  

int main(int argc, char* argv[])
{
    int p, rank;
    int n = atoi(argv[1]);
    int flag = atoi(argv[2]);
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &p);
    int num=n/p,k;
    int arr[num];
    if(flag==0){ //Block distribution
        num = n/p;
        if(rank==p-1)
        {
            num+=(n%p);
        }
        for(int i=0;i<num;i++)
        {
            if(rank==p-1)
            {
                arr[i] = (num-n%p)*rank+i;
            }
            else
            {
                arr[i] = num*rank+i;
            }
        }
    }
    if(flag==1){//Cyclic Distribution
        num = n/p;
        if(n%p>rank)
        {
            num+=1;
        }
        k = rank;
        for(int i=0;i<num;i++)
        {
            arr[i] = k;
            k+=p;
        }
    }
    if(flag==2){//Block cyclic distribution
        int r = 2;
        int b = n/r;
        int x = n%r;
        num = (b/p)*r;
        if(b%p>rank)
        {
            num+=r;
        }
        if(rank==b%p)
        {
            num+=x;
        }
        k = r*rank;
        for(int i=0;i<num;i++)
        {
            if(i%2==0)
            {
                arr[i] = k;
            }
            else
            {
                arr[i] = k+1;
                k+=r*p;
            }
        }
    }
    MPI_Barrier(MPI_COMM_WORLD);

    int local_sum = 0,i;
    for (i = 0; i < num; i++)
        local_sum += arr[i];
    int total_sum = 0;
    MPI_Reduce(&local_sum, &total_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    if (rank == 0)
    {
        printf("Total Sum:%d\n", total_sum);
    }
    MPI_Finalize();
}