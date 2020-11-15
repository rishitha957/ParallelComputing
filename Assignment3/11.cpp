#include <bits/stdc++.h>
#include <mpi.h>
#include <thread>
#include <mutex>

using namespace std;
int count1 = 0;
mutex mtx;
int num_threads = 2;
int msg = 1;
void iittp_barrier(int rank, int np, int tid, int num_threads){
    if(rank==0&&tid==0){
        MPI_Send(&msg,1,MPI_INT,1,1,MPI_COMM_WORLD);
        MPI_Recv(&msg,1,MPI_INT,np-1,1,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
    }
    else if(tid==0){
        MPI_Recv(&msg,1,MPI_INT,rank-1,1,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        MPI_Send(&msg,1,MPI_INT,(rank+1)%np,1,MPI_COMM_WORLD);
    }
    if(tid==0){
        MPI_Bcast( &msg , 1, MPI_INT, 0, MPI_COMM_WORLD);
    }
    mtx.lock();
    count1++;
    mtx.unlock();
    while((count1%num_threads)!=0);
}
void thread_func(int tid,int &val,int rank,int np,int n_threads)
{
    cout<<"rank - "<<rank<<" tid - "<<tid<<" val: "<<val<<endl;
    iittp_barrier(rank,np,tid,num_threads);
}
int main(int argc, char **argv)
{
    int rank, np;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &np);
    int n_thread = 4;
    srand(time(NULL));
    int val = rand()%100;
    cout<<"rank - "<<rank<<": "<<val<<endl;
    vector<thread> threads;
    for(int i=0;i<n_thread;i++){
        threads.push_back(thread(thread_func,i,ref(val),rank,np,n_thread));
    }
    for(auto &th:threads){
        th.join();
    }
    cout<<"rank - "<<rank<<": "<<val<<endl;
    MPI_Finalize();
}