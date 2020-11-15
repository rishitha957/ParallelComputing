#include <bits/stdc++.h>
#include <omp.h>

using namespace std;

int main(int argc, char** argv){
    int m = atoi(argv[1]);
    int n = atoi(argv[2]);
    int p = atoi(argv[3]);
    int a[m][n], b[n][p], c[m][p];
    srand(time(NULL));
    cout<<"A - "<<endl;
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            a[i][j] = rand()%10;
            cout<<a[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
    cout<<"B - "<<endl;
    for(int i=0;i<n;i++){
        for(int j=0;j<p;j++){
            b[i][j] = rand()%10;
            cout<<b[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
    int i,j,k;
    #pragma omp parallel for private(i,j,k)
        for(i=0;i<m;i++){
            for(j=0;j<p;j++){
                c[i][j] = 0;
                for(k=0;k<n;k++){
                    c[i][j] += (a[i][k]*b[k][j]);
                }
            }
        }
    cout<<"C - "<<endl;
    for(int i=0;i<m;i++){
        for(int j=0;j<p;j++){
            cout<<c[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
}