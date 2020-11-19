#include <bits/stdc++.h>
#include <omp.h>
#include <random>
#include <chrono>
#include <mutex>

using namespace std;
using namespace std::chrono;

#define gc getchar_unlocked
#define fl(i,n) for(int i=0;i<n;i++)
#define fl1(i,a,b) for(int i=a;i<b;i++)
#define sz() size()
#define pb(x) push_back(x)
#define ll long long
#define f first
#define s second
#define outc(x) cout<<x<<endl
#define out(x) cout<<#x " - "<<x<<" "
#define outn(x) cout<<#x " - "<<x<<endl
#define be(x) x.begin(), x.end()
#define out1D(v) for(int i=0;i<v.size();i++){cout<<v[i]<<" ";}cout<<endl;
#define out2D(v) for(int i=0;i<v.size();i++){for(int j=0;j<v[i].size();j++){cout<<v[i][j]<<" ";}cout<<endl;}
typedef pair<int, int>	pii;
typedef pair<ll, ll>	pl;
typedef vector<int>		vi;
typedef vector<float>	vf;
typedef vector<double>	vd;
typedef vector<ll>		vl;
typedef vector<pii>		vpii;
typedef vector<pl>		vpl;
typedef vector<vi>		vvi;
typedef vector<vf>		vvf;
typedef vector<vl>		vvl;
typedef vector<vd>	    vvd;

int main(int argc, char **argv){
    if(argc!=4){
        outc("Usage: ./pgm <matrix_size> <threshold>");
    }
    double lb = 0, ub = 10;
    int n = atoi(argv[1]);
    double threshold = atof(argv[2]);
    uniform_real_distribution<double> urd(lb,ub);
    default_random_engine re;

    int num_threads = atoi(argv[3]);
    // out(num_threads);
    omp_set_num_threads(num_threads);
    out(num_threads);
    // initialize array with padding !!

    vvd mat,mat_new;
    vd temp_pad(n+2,0);
    mat.pb(temp_pad);
    fl(i,n){
        vd temp,temp1;
        temp.pb(0);
        fl(j,n){
            temp.pb(urd(re));
        }
        temp.pb(0);
        mat.pb(temp);
    }
    mat.pb(temp_pad);
    mat_new = mat;
    // out2D(mat);
    //starting computation - 
    auto start = high_resolution_clock::now();

    int iter = 0, end_loop = 0;
    while(end_loop == 0){
        int diff = INT_MIN;
        iter++;
        #pragma omp parallel shared(diff)
        {
            #pragma omp for schedule(static)
            fl1(i,1,n+1){
                fl1(j,1,n+1){
                    mat_new[i][j] = 0.2*(mat[i][j]+mat[i-1][j]+mat[i+1][j]+mat[i][j-1]+mat[i][j+1]);
                    int diff1 = abs(mat_new[i][j]-mat[i][j]);
                    if(diff1>=diff) diff = diff1;
                }
            }
            #pragma omp barrier
            if(diff<=threshold){
                end_loop = 1;
            }
        }
        #pragma omp parallel
        {
            mat = mat_new;
        }
        // out2D(mat);
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop-start);
    out(n);
    outn(duration.count());
    return 0;
}