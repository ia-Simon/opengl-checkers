# OpenGL Checkers

A simple checkers game developed entirely using the basics of OpenGL, using a lightweight audio engine library.

## Graphics Engine

The library used for rendering is OpenGL/GLUT. It is usually installed by default on MacOSX machines, but needs to be installed 
in Linux distros.


## Audio Engine

The library chosen for audio reprodution is [IrrKlang](https://www.ambiera.com/irrklang/).


## Build and Run

To run this application, simply execute de Makefile command according to your platform. There may be some initial steps required 
before running the game, which will be covered individually below.

### OS: Linux

1. Install the free and open source distribution of OpenGL/GLUT following the steps below:
```sh
$ sudo apt update
$ sudo apt install freeglut3-dev
```

2. Call the Make command for Linux:
```sh
$ make run-linux
```

### OS: MacOSX

1. Call the Make command for MacOSX:
```sh
$ make run-macosx
```

## Controls
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