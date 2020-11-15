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


typedef struct{
    int p;
    int dims[2];
    MPI_Comm comm2D;
    int coords[2];
    int g_rank;
}Grid;

void setup(Grid* grid, int rank){
    int q = (int)sqrt(grid->p);
    grid->dims[0] = q;
    grid->dims[1] = q;
    MPI_Dims_create(grid->p, 2, grid->dims);
    int periods[] = {1,1}; //horizantal and vertical wraparound
    grid->coords[2];
    grid->comm2D;

    MPI_Cart_create(MPI_COMM_WORLD, 2, grid->dims, periods, 1, &grid->comm2D);
    
    MPI_Cart_coords(grid->comm2D, rank, 2, grid->coords);
    MPI_Cart_rank(grid->comm2D, grid->coords, &grid->g_rank);
}

int main(int argc, char **argv){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    srand(chrono::high_resolution_clock::now().time_since_epoch().count());

    MPI_Init(&argc, &argv);
	
    int rank, np;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &np);

    int n = atoi(argv[1]);
    
    int s = atoi(argv[2]),d = atoi(argv[3]);

    if(argc!=4){
        cout<<"Usage: mpiexec -np <np> ./1 <no.of nodes> <source> <dest> !"<<endl;
        MPI_Abort(MPI_COMM_WORLD,1);
        return 0;
    }

    ifstream fin("adj_mat.txt");
    int q = (int)sqrt(np);

    int A[q][q], B[q][q], C[q][q];
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
            C[i][j] = 0;
            // out(rank);
            // outn(buffer);
        }
    }

    Grid grid;
    grid.p = np;

    setup(&grid,rank);

    //check where A[s][d] is present!!
    int temp = n/q;
    int coord_sd[] = {s/temp,d/temp};

    MPI_Barrier(MPI_COMM_WORLD);
    
    int path_exits = 0;
    int my_rank;

    if(grid.coords[0]==coord_sd[0] && grid.coords[1]==coord_sd[1]){
        int i = s%temp;
        int j = d%temp;
        if(A[i][j] != 0){
            path_exits = 1;
        }
    }
    // check_path_exists(dims[0],coords,coord_sd,path_exits,A);
    
    MPI_Cart_rank(grid.comm2D, coord_sd, &my_rank);
    MPI_Bcast(&path_exits, 1, MPI_INT, my_rank, grid.comm2D);
    
    // MPI_Cart_rank( MPI_Comm comm , const int coords[] , int* rank);
    
    int iter = 0;
    while(path_exits==0 && iter<=n){
        iter++;
        int right=0,left=0,down=0,up=0;
        MPI_Comm_rank(grid.comm2D, &rank);
        MPI_Cart_coords(grid.comm2D, rank, 2, grid.coords);

        //create initial skew matrix

        MPI_Cart_shift(grid.comm2D, 1, grid.coords[0], &left, &right); 
        // 1 - row, dist - coords[0], left,right neighbours value will be o/p
        MPI_Cart_shift(grid.comm2D, 0, grid.coords[1], &up, &down);
        MPI_Sendrecv_replace(&(A[0][0]), grid.dims[0]*grid.dims[1], MPI_INT, left, 0, right, 0, grid.comm2D, MPI_STATUS_IGNORE);
        MPI_Sendrecv_replace(&(B[0][0]), grid.dims[0]*grid.dims[1], MPI_INT, up, 0, down, 0, grid.comm2D, MPI_STATUS_IGNORE);
        fl(row,q){
            fl(i,q){
                fl(j,q){
                    int sum = 0;
                    fl(k,q){
                        sum+= A[i][k]*B[k][j];
                    }
                    C[i][j] += sum;
                }
            }
            MPI_Cart_shift(grid.comm2D, 1, 1, &left, &right);
            MPI_Cart_shift(grid.comm2D, 0, 1, &up, &down);
            MPI_Sendrecv_replace(&(A[0][0]), grid.dims[0]*grid.dims[1], MPI_INT, left, 0, right, 0, grid.comm2D, MPI_STATUS_IGNORE);
            MPI_Sendrecv_replace(&(B[0][0]), grid.dims[0]*grid.dims[1], MPI_INT, up, 0, down, 0, grid.comm2D, MPI_STATUS_IGNORE);
        }
        MPI_Barrier(grid.comm2D);

        // check_path_exists(dims[0],coords,coord_sd,path_exits,C);

        if(grid.coords[0]==coord_sd[0] && grid.coords[1]==coord_sd[1]){
            int i = s%temp;
            int j = d%temp;
            if(A[i][j] != 0){
                path_exits = 1;
            }
        }

        MPI_Cart_rank(grid.comm2D, coord_sd, &my_rank);
        MPI_Bcast(&path_exits, 1, MPI_INT, my_rank, grid.comm2D);

        outn(rank);

        fl(i,q){
            fl(j,q){
                A[i][j] = C[i][j];
                C[i][j] = 0;
                // out(A[i][j]);
            }
            // outn("");
        }
        
    }

    if(rank==0){
        // out(coord_sd[0]);
        // out(coord_sd[1]);
        // MPI_Cart_rank( comm2D, coord_sd, &my_rank);
        // outn(my_rank);
        // outn(iter);
        if(iter<=n){
            out(path_exits);
            cout<<"length - "<<iter+1<<endl;
        }
        else
        {
            outn("path doesn't exist!");
        }
    }

    MPI_Finalize();
    return 0;
}