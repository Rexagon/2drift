# 2drift
Simple 2D drifting game

## Build
Install SFML and entt somewhere in your system and then:
```
$ mkdir CMakeFiles && cd CMakeFiles
$ cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release \
    -DSFML_DIR=/path/to/sfmlconfig \ 
    -Dentt_DIR=/path/to/enttconfig \ 
    ..
$ cmake --build .
```
