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

## Sound Library
---
The library chosen for sound reprodution is [IrrKlang](https://www.ambiera.com/irrklang/).

To install the library manually, follow the steps below:

1. Extract `irrKlang.tar.gz` somewhere safe, where you're sure not to delete it accidentally, *e.g.* `/usr/local/Ext/` (UNIX-like system). Below is the command for UNIX-like systems:
    ```sh
    $ tar -xzvf irrKlang.tar.gz irrKlang
    ```

2. Symlink/copy all header files from `irrKlang/include/` to a directory your editor/compiler is aware of, *e.g.* `/usr/local/include/` on Linux.

3. Symlink/copy all compiled lib files from `irrKlang/bin/<your-OS-folder>` to a directory your editor/compiler is aware of, *e.g.* `/usr/local/lib/` (UNIX-like system). The compiled lib file changes according to your OS:

        MacOSX:   `irrKlang/bin/macosx-gcc/*.dylib`
        Linux:    `irrKlang/bin/linux-gcc-64/*.so`
        Windows:  `irrKlang/bin/winx64-visualStudio/*.dll`

    3.1. If on Linux, run `ldconfig` to update the library linker list of known libraries

4. Compile the program with the flags **-lIrrKlang** and **-pthread** if on a UNIX-like system (no idea how it would be done on Windows).

## Compilation
---
This project was developed using OpenGL/GLU/GLUT + IrrKlang, on a C++17 syntax.

Compile with the flags for OpenGL/GLU/GLUT and IrrKlang libs, and `--std=c++17` for a compiler with c++17 capabilities.

Compile the game in the same folder as src/, audios/ and textures/.

Below are the commands used to compile this game in Linux and MacOSX:
```sh
linux>$ g++ src/main.cpp --std=c++17 -lGL -lGLU -lglut -lIrrKlang -pthread -o checkers

macosx>$ g++ src/main.cpp --std=c++17 -framework OpenGL -framework GLUT -lIrrKlang -pthread -o checkers
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