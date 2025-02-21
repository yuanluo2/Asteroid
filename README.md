# Asteroid
Asteroid game. written in C++14, with SFML. This is just a learning project, not so much fun.
Just use your directional keys to control movement, lose focus or press ESC key to pause.

##### I test it with my winlibs-x86_64-posix-seh-gcc-14.1.0-mingw-w64msvcrt-11.0.1-r1 on my windows desktop, the build system use CMake, the compile command is:
``` shell
cd Asteroid

mkdir build
cd build

cmake -G "MinGW Makefiles" -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++ ..
mingw32-make -j 4
```
