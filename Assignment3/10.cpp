#include <bits/stdc++.h>
#include <mpi.h>

using namespace std;
int main(int argc, char **argv)
{
    int rank, np;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &np);
    int n = atoi(argv[1]);
    int m = atoi(argv[2]);
    int a[n];
    for (int j = 0; j < np; j++)
    {
        if (rank == j)
        {
            cout<<"Rank - "<<rank<<endl;
            for (int i = 0; i < n; i++)
            {
                a[i]=rank;
                cout<<a[i]<<" ";
            }
            cout<<endl;
        }
        MPI_Barrier(MPI_COMM_WORLD);
    }
    int cur=0,val;
    for(int i=0;i<m;i++)
    {
        if(cur==rank)
        {
            val=rand()%np;
        }
        MPI_Bcast(&val,1,MPI_INT,cur,MPI_COMM_WORLD);
        if(val==cur)
            continue;
        if(cur==rank)
        {
            MPI_Send(&a[0],n,MPI_DOUBLE,val,1,MPI_COMM_WORLD);
        }
        if(rank==val)
        {
            MPI_Recv(&a[0],n,MPI_DOUBLE,cur,1,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        }
        cur=val;
        MPI_Barrier(MPI_COMM_WORLD);
    }
    
    for (int j = 0; j < np; j++)
    {
        if (rank == j)
        {
             cout<<"Rank - "<<rank<<endl;
            for (int i = 0; i < n; i++)
            {
                cout<<a[i]<<" ";
            }
            cout<<endl;
        }
        MPI_Barrier(MPI_COMM_WORLD);
    }
    
    MPI_Finalize();
}