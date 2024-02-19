# mini-map-generation

This is an very very basic example of an procedural map generation algorithm, which was quickly coded for an procedural map generation presentation the night before.
The map only consists of three blocks (4 if you count air).

Those are:

- Stone
- Grass
- Water
- (Air)

## Install

The Project is coded in c and for rendering we use the library raylib (version 4.5).
To **run** the project install an c compiler and install [raylib](https://www.raylib.com)

## Code adjustments for diffrent results

### Size of map

To change the size of map just change the makros at the beginning of the c file. Altough you probably need to change the starting position of the camera, so you can see the whole map.

```c
#define MAP_X 12
#define MAP_Y 10
#define MAP_Z 7
```

### Chances of blocks

To change the chances of blocks like water or width of mountains go into the code (its commented)

## Info

This Project was coded in 1h at home and is not good at all. Its as mentioned at top just an little example for an presentation and I am pretty sure I won't change the code later on
