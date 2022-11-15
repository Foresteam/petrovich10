# petrovich10
10 laba, SFML.
My homework (a game written in C++, cross-platform).

## Run on Linux
1. Install SFML 2.5.1 and the [listed SO libraries](https://www.sfml-dev.org/tutorials/2.5/compile-with-cmake.php#installing-dependencies)
2. Download a binary distribution

## Run on Windows
Download a binary distribution

## Build on Linux
1. Install SFML, CMake, C++ build tools
2. Install the [listed libraries](https://www.sfml-dev.org/tutorials/2.5/compile-with-cmake.php#installing-dependencies)
3. Install (or install-extract) [libforesteamnd](https://github.com/Foresteam/foresteamnd)
4. Clone the repository
5.
```bash
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make -jNUMBER_OF_THREADS
```
OR run **pack_appimage.sh**

## Build on Windows
1. Install CMake, MinGW and add them to PATH
2. Clone the repository
3. Install-extract [libforesteamnd](https://github.com/Foresteam/foresteamnd) into the project folder (**include** and **lib**). *If it argues that it can't find **libforesteamnd.a** then copy it manually to **lib**.*
4. Copy **SFML/bin**, **SFML/include**, **SFML/lib** to the project directory
5. Create **build** folder in the project directory
6. Copy the contents of SFML/bin to that folder
7. Open **build** folder in terminal (powershell, for example)
```bash
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build . -G "MinGW Makefiles" --config Release
```