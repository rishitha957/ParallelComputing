#include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;

const int nthreads = 4;
int64_t ndata = 100;
mutex mtx;

int total_sum = 0;
int sum[nthreads] = { 0 };

void compute_sum(int tid, vector<int>& d)
{
  int st = (ndata / nthreads) * tid;
  int en = (ndata / nthreads) * (tid + 1);
  
  for (int i = st; i < en; i++) {
    sum[tid] += d[i];
  }
}

int main(int argc, char ** argv)
{
  vector<thread> threads;
  vector<int> data;
  ndata = atoi(argv[1]);
  cout<<ndata<<endl;
  for (int i = 0; i < ndata; i++) {
    data.push_back(rand()%10);
  }
  auto start = high_resolution_clock::now();
  for (int i = 0; i < nthreads; i++) {
    threads.push_back(thread(compute_sum, i, ref(data)));
  }
  
  for (auto &th : threads) {
    th.join();
  }
  int tsum = 0;
  for (int i = 0; i < nthreads; i++) {
    tsum += sum[i];
  }
  cout<<"total sum = "<<tsum<<endl;
  auto stop = high_resolution_clock::now();
  auto duration = duration_cast<microseconds>(stop - start);
  cout << duration.count() << endl;
  return 0;
}