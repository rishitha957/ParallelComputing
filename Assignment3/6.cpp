#include <bits/stdc++.h>
#include<omp.h>
using namespace std;
int main(int argc,char** argv)
{
    int n=atoi(argv[1]);
    int a[n];
    int sum=0;
    srand(time(NULL));
    for(int i=0;i<n;i++)
    {
        a[i]=rand()%10;
        cout<<a[i]<<" ";
    }
    cout<<endl;
    #pragma omp parallel for reduction(+: sum)
    for(int i=0;i<n;i++)
    {
        sum+=a[i];
    }
    cout<<"Sum - "<<sum<<endl;
}
