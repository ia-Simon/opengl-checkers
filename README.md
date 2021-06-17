# Checkers Game

## General
---
Group components:

* Igor Amaral Simon:    24887
* Cláudio Rocha:        108646
* Lucca Marques:        30764
* Daniel Veronez:       107880
* Evelyn Volf:          106981

[Github Repository](https://github.com/ia-Simon/opengl-checkers.git)

## Sound Lib
---
The library chosen for sound reprodution was [IrrKlang](https://www.ambiera.com/irrklang/).

To install the library, follow the steps below:
1. Unzip the `irrKlang.zip` archive somewhere safe in your computer, where you are sure not to delete it accidentally, *e.g.* `/usr/local/CustomFolder/irrKlang/` if you are on Linux.
2. Symlink/copy all header files from `irrKlang/include/` to a directory your editor/compiler is aware of *e.g.* `/usr/local/include/` on Linux.
3. Grab the pre-compiled lib files from `irrKlang/bin/yourOSfolder/` according to your OS, and symlink/copy them to a directory your compiler is aware of *e.g.* `/usr/local/lib/` on Linux. If on Linux run ldconfig to update the library linker known libraries
    * MacOS X:  `macosx-gcc/*.dylib`
    * Linux:    `linux-gcc-64/*.so`
    * Windows:  `winx64-visualStudio/*.dll`
4. Compile the program with the flag *-lIrrKlang* if on Linux/MacOS (no idea on how it would work on Windows). If on Linux, also include *-pthread* since irrKlang uses it.

## Compilation
---
This project was developed using OpenGL/GLU/GLUT + IrrKlang, using C++17 syntax

Compile with the flags for OpenGL/GLU/GLUT and IrrKlang libs, and `--std=c++17` for a compiler with c++17 capabilities.

Compile the game in the same folder as src/, audios/ and textures/.

On Linux, the compilation command should look something like:
```
g++ src/main.cpp --std=c++17 -lGL -lGLU -lglut -lIrrKlang -pthread -o checkers
```

## Controls
---
```
 [Keyboard]                          | [Mouse]  _______
                    ...   {-} {=}    |        /{M1}|    \
      {Q}   {E}    ...     {[} {]}   |       | --------- |
          {S}       ...              |       |           |
{Shift} {Z}   {C}    ...             |        \         /
                                     |          -------
```
* Keyboard:
    * Q: Move Up-Left
    * E: Move Up-Right
    * S: Skip Round
    * Z: Move Down-Left
    * C: Move Down-Right
    * [: Select previous piece
    * ]: Select next piece
    * -: Decrease mouse sensitivity
    * =: Increase mouse sensitivity
    * Shift: Changes the action done by the mouse Y-axis
* Mouse:
    * M1: Moves the camera
        * X-axis: Moves the camera around a circle of mutable radius
        * Y-axis: If {Shift} is active, changes the height Y of the camera; otherwise changes the radius of the circle