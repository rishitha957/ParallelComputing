## Iterative stencil computation

### How to test?
Running Makefile generates executable. And you can test the executable 'pgm'
```
make
./pgm <mat_size> <threshold> <n_threads>
```
Or you can directly run the shell script, after changing permissions. Currently it tests for different matrix sizes.
```
chmod +x shell1.sh
./shell1.sh
```

### Performance !
The program is tested for different matrix sizes and with different number of threads, to find the ideal no. of threads.

![6](https://user-images.githubusercontent.com/46604699/102690319-92917d00-422a-11eb-92cc-57cead9b63c8.JPG)

Sytem specific info:
![8](https://user-images.githubusercontent.com/46604699/102690573-59f2a300-422c-11eb-94d4-19947c8b1826.JPG)

Also, If it's (mostly) CPU bound, then slightly over the number of available processors is probably best [1]. So I fixed the no.of threads to be 6, as I have 4 cores. 

Final results:
![7](https://user-images.githubusercontent.com/46604699/102690320-96250400-422a-11eb-9d2e-5dc589102a1d.JPG)

Note: Program uses vectors. Whenever older vector and new one needs to be swapped, we use assignment operator which swaps it in linear time. (or if the arrays are used, instead of copying the whole array, swapping pointers will help)

### References
[1] Ideal no. of threads - https://stackoverflow.com/questions/42015714/how-to-get-an-ideal-number-of-threads-in-parallel-programs-in-java