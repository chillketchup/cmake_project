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
cmake ..
cmake --build .
```

Then, to run the program
```bash
./cmake_project
```
