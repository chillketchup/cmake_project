## Prerequisites
You will need the following installed\
Open Terminal and enter the following commands\
homebrew:
```bash
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
```
git and cmake:
```bash
brew install git
brew install cmake
```

## Cloning the repository
Click the green "code" button and copy the web URL
<img width="1512" alt="cloning repository1" src="https://github.com/user-attachments/assets/913b12d0-8a0c-4bce-aaa5-a1a2b492a1ba" />

Then, open terminal and enter the following commands (replace the items in <> with what you are using)
```bash
cd <directory>
git clone <web URL>
```

a folder containing the cloned repository should then show up in the directory

## Building using CMake
Open Terminal and enter the following commands to create a build directory and run CMake (replace the items in <> with what you are using)
```bash
cd <repository>
mkdir build
cd build
cmake ..
cmake --build .
```

Then, to run the program
```bash
./<program_name>
```
or run the executables created in the build folder

## Optimising code
The matrix_multiplication.cpp program contains two functions that both do matrix multiplication, but one is optimised to be much faster

average runtime for 512x512 size matrix\
naive:     0.5696186 seconds\
optimised: 0.1969296 seconds (**189%** faster)

average runtime for 800x800 size matrix\
naive:     2.02847 seconds\
optimised: 0.759335 seconds (**167%** faster)

the naive function uses a 2D vector, where rows are stored seperately in memory. On the other hand, the optimised function uses a 1D array, where all the data is contiguous. This improves cache locality, making data faster to access.

The naive function loops in the order ijk, which iterates through B first by column, then by row. Columns are not sequential in memory, so a new cache line will need to be loaded every time B[k][j] is accessed. The optimised instead loops in the order ikj, which iterates through B first by row, then by column. Rows are sequential in memory, so every cache line contain many useful values, making data access faster.

Additionally, the naive function has to load A[i][k] from memory for every j, but the optimised function only loads A[i*N + k] once for all j.

## Parallelization 
Farthest_points.cpp contains a program that find the farthest two points from a set of 3D points. This can be made more efficient by splitting the data into multiple chunks which are processed in parallel, and then combined togther for the final answer.

<img width="684" height="573" alt="farthest points program diagram" src="https://github.com/user-attachments/assets/10dbcb75-473f-451c-81c0-64a70eda1d2e" />

The above diagram shows how the program works.

First, the array of data is split into a number of chunks, with each chunk being formed by taking unprocessed points from both the front and back of the array. Later points require fewer calculations than earlier points, so splitting the data this way ensures all threads finish at the same time and thus no time is waste. 

Then, each chunk is processed seperately. For each point, the program check the distance between the point and all other subsequent points, and tracks both the farthest pair of points found so far and their distance. The farthest pair of points found in the chunk are then returned.

Lastly, the main program compares the farthest pair of points found in each chunk to find the overall farthest pair of points, which is then outputted.

This program does not actually implement multithreading, and is rather just a proof of concept. The parallel structure is simulated in a single thread. There are many challenges that come with implementing parallelism:

1. Data synchronization - it is possible that multiple threads read/write shared data at the same time (race conditions), which can cause unpredictable behaviour and errors during result aggregation. For example, if two threads try to increment a counter, currently at 3, by 1, the same time, they will both read 3 and write 4, causing the counter's final value to be 4 when it should be 5. A possible solution is using atomic variables which prevents race conditions from happening.
2. Load balancing - As the data given to each thread is different, it is possible that some threads may finish early while others take much longer, which reduces efficiency. This can be solved within the logic of the program by ensuring threads receive data that takes a similar amount of time to process, or if this is not possible, allow idle threads to take work from busy ones. 
3. Scalability - It is possible that adding more threads will not increase the efficiency of the program. This is because certain parts of the program, such as distributing data and result aggregation, become slower the more threads there are.
4. False sharing - Even if two threads are modifying two different variables, if those variables are on the same cache line, the cache line is reloaded even though this is not necessary (as the threads are not actually sharing data), slowing down the program. Solutions to this include padding to make sure variables are in seperate cache lines or using thread local storage.
