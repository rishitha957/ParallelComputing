#include <bits/stdc++.h>

using namespace std;

int main(int argc, char **argv){
    ofstream f;
    f.open("adj_mat.txt");
    if(argc!=2){
        cout<<"Usage: ./dump_graph <no.of nodes>"<<endl;
        return 0;
    }
    int n = atoi(argv[1]);
    cout<<n<<endl;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            f<<rand()%2;
        }
        f<<"\n";
    }
    f.close();
    return 0;
}