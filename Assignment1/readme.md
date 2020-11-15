## How to test?
```
make
```
This will generate two executables, dump_graph and 1

To dump a random graph in adj_matrix.txt

```
./dump_graph <no.of nodes>
```
let n be no. of nodes. And p be no.of processes. Ensure that, n should be multiple of $ \sqrt{p} $ Then, to test the main script:
```
mpiexec -np <np> ./1 <no.of nodes> <source> <dest>
```

or I've written a shell script, with the same above commands, modify the np, and no. of nodes, and run the same, after changing the permissions.

```
chmod +x shell1.sh
./shell1.sh
```

## Matrix Multiplication Algorithm - (wrap around shift!)
![1](https://user-images.githubusercontent.com/46604699/102443565-142bb400-404d-11eb-8775-1734d6955078.JPG) 

After initial skewing of matrices, resultant A and B matrices.

![2](https://user-images.githubusercontent.com/46604699/102443599-2574c080-404d-11eb-9f2b-dbb4e78c35e9.JPG)

Step - 2: Shift and multiply

|![3](https://user-images.githubusercontent.com/46604699/102443623-31f91900-404d-11eb-9e06-d2fc49827a6a.JPG)|![4](https://user-images.githubusercontent.com/46604699/102443641-3de4db00-404d-11eb-934b-f564b9053b61.JPG)|![5](https://user-images.githubusercontent.com/46604699/102443661-4806d980-404d-11eb-9ff8-4de2529d49f4.JPG)|
|:--:|:--:|:--:|

## References
[1] MPI Topologies and Cartesian comms - https://edoras.sdsu.edu/~mthomas/sp17.605/lectures/MPI-Cart-Comms-and-Topos.pdf

[2] Cannon's Algorithm - http://cseweb.ucsd.edu/classes/fa12/cse260-b/Lectures/Lec13.pdf
