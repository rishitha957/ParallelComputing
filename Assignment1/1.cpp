#include<bits/stdc++.h>
#include "mpi.h"

using namespace std;

#define gc getchar_unlocked
#define fl(i,n) for(int i=0;i<n;i++)
#define sz() size()
#define pb(x) push_back(x)
#define ll long long
#define f first
#define s second
#define out(x) cout<<#x " - "<<x<<" ";
#define outn(x) cout<<#x " - "<<x<<endl;
#define be(x) x.begin(), x.end()
#define out1D(v) for(int i=0;i<v.size();i++){cout<<v[i]<<" ";}cout<<endl;
#define out2D(v) for(int i=0;i<v.size();i++){for(int j=0;j<v[i].size();j++){cout<<v[i][j]<<" ";}cout<<endl;}
typedef pair<int, int>	pii;
typedef pair<ll, ll>	pl;
typedef vector<int>		vi;
typedef vector<ll>		vl;
typedef vector<pii>		vpii;
typedef vector<pl>		vpl;
typedef vector<vi>		vvi;
typedef vector<vl>		vvl;

int main(int argc, char **argv){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    srand(chrono::high_resolution_clock::now().time_since_epoch().count());

    MPI_Init(&argc, &argv);
	
    int rank, np;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &np);

    int n = atoi(argv[1]);
    int A[n][n], B[n][n];
    
    int s = atoi(argv[2]),d = atoi(argv[3]);
    if(argc!=4){
        cout<<"Usage: mpiexec -np <np> ./1 <no.of nodes> <source> <dest> !"<<endl;
        MPI_Abort(MPI_COMM_WORLD,1);
        return 0;
    }

    ifstream fin("adj_mat.txt");
    int q = (int)sqrt(np);
    fl(i,q){
        fl(j,q){
            int x = rank/q;
            int y = rank%q;
            int i1 = (i*(n+1));
            int seek_val = (x*(n+1)*q) + (y*q) + i1 + j;
            // out(seek_val);
            fin.seekg(seek_val);
            char buffer[1];
            fin.read(buffer,1);
            A[i][j] = atoi(buffer);
            B[i][j] = atoi(buffer);
            // out(rank);
            // outn(buffer);
        }
    }
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Finalize();
    return 0;
}