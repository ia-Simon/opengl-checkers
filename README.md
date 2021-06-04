# Checkers Game

## Sound Lib
---
The library chosen for sound reprodution was [IrrKlang](https://www.ambiera.com/irrklang/).

To install the library, follow the steps below:
1. Unzip the `irrKlang.zip` archive somewhere safe in your computer, where you are sure not to delete it accidentally *e.g.* `/usr/local/CustomFolder/irrKlang/` if you are on Linux.
2. Symlink/copy all header files from `irrKlang/include/` to a directory your editor/compiler is aware of *e.g.* `/usr/local/include/` on Linux.
3. Grab the pre-compiled lib files from `irrKlang/bin/yourOSfolder/` according to your OS, and symlink/copy them to a directory your compiler is aware of *e.g.* `/usr/local/lib/` on Linux.
    * MacOS X:  `macosx-gcc/*.dylib`
    * Linux:    `linux-gcc-64/*.so`
    * Windows:  `winx64-visualStudio/*.dll`
4. Compile de program with the flag *-lirrKlang* if on Linux/MacOS (no idea on how it would work on Windows).

## Compilation
---
This project was developed using OpenGL/GLU/GLUT + IrrKlang, using C++17 syntax

Compile with the flags for OpenGL/GLU/GLUT and IrrKlang libs, and `--std=c++17` for a compiler with c++17 capabilities.