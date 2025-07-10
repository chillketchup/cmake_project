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

## Naive vs optimised matrix multiplication function
The matrix_multiplication.cpp program contains two functions that both do matrix multiplication, but one is optimised to be much faster

average runtime for 512x512 size matrix\
naive:     0.5696186 seconds\
optimised: 0.1969296 seconds (**189%** faster)

the naive function uses a 2D vector, where rows are stored seperately in memory. On the other hand, the optimised function uses a 1D array, where all the data is contiguous. This improves cache locality, making data faster to access.

The naive function loops in the order ijk, which iterates through B first by column, then by row. Columns are not sequential in memory, so a new cache line will need to be loaded every time B[k][j] is accessed. The optimised instead loops in the order ikj, which iterates through B first by row, then by column. Rows are sequential in memory, so every cache line contain many useful values, making data access faster.

Additionally, the naive function has to load A[i][k] from memory for every j, but the optimised function only loads A[i*N + k] once for all j.
