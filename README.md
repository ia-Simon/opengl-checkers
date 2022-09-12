# Checkers Game

## General
---
Simple checkers game written in pure OpenGL.

## Sound Library
---
The library chosen for sound reprodution is [IrrKlang](https://www.ambiera.com/irrklang/).

To install the library manually, follow the steps below:

1. Extract `irrKlang.tar.gz` somewhere safe, where you're sure to not delete it, *e.g.* `/usr/local/Ext/`.

```sh
$ sudo mkdir /usr/local/Ext
$ cd /usr/local/Ext
$ sudo tar -xzvf irrKlang.tar.gz irrKlang
```

2. Symlink/copy all header files from `./irrKlang/include/` to a directory your editor/compiler is aware of, *e.g.* `/usr/local/include/`.

```sh
$ sudo ln -s $(pwd)/irrKlang/include/*.h  /usr/local/include/
```

3. Symlink/copy all compiled lib files from `./irrKlang/bin/<your-os-folder>/` to a directory your editor/compiler is aware of, *e.g.* `/usr/local/lib/`.

```sh
# MacOSX:   
# irrKlang/bin/macosx-gcc/*.dylib
# 
# Linux:    
# irrKlang/bin/linux-gcc-64/*.so
#
# Windows:  
# irrKlang/bin/winx64-visualStudio/*.dll
$ sudo ln -s $(pwd)/<path/to/your/os/libs>  /usr/local/lib/
```

4. If on Linux, run `ldconfig` to update the library linker list of known libraries.

```sh
$ sudo ldconfig
```

## Compilation
---
This project was developed using OpenGL/GLU/GLUT + IrrKlang, on a C++17 syntax. OpenGL should be installed by default in MacOSX; to install it on Linux, use the following command:

```sh
# Linux:
$ sudo apt update
$ sudo apt install freeglut3-dev
```

Compile with the flags for OpenGL/GLU/GLUT and IrrKlang libs, and `--std=c++17` for a compiler with c++17 capabilities.

Compile the game in the same folder as src/, audios/ and textures/.

Below are the commands used to compile this game in Linux and MacOSX:
```sh
# Linux:
$ g++ src/main.cpp --std=c++17 -lGL -lGLU -lglut -lIrrKlang -pthread -o checkers

# MacOSX:
$ g++ src/main.cpp --std=c++17 -framework OpenGL -framework GLUT -lirrklang -pthread -o checkers
```

## Controls
---
```
 [Keyboard]                          | [Mouse]  _______
                                     |        /{M1}|    \  
{Esc}                                |       |     |     |  
                    ...   {-} {=}    |       |-----------|
      {Q}   {E}    ...     {[} {]}   |       |           |
          {S}       ...              |        \         /
{Shift} {Z}   {C}    ...             |          -------
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
    * Esc: quits from the game
* Mouse:
    * M1: Moves the camera
        * X-axis: Moves the camera around a circle centered on the middle of the table
        * Y-axis: If {Shift} is active, changes the height Y of the camera; otherwise changes the radius of the circle (a.k.a. the distance from the table)