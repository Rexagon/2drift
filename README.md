# 2drift
Simple 2D drifting game

## Build
Install SFML somewhere in your system and then:
```
git clone https://github.com/Rexagon/2drift.git
cd 2drift
mkdir CMakeFiles && cd CMakeFiles
cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release -DSFML_DIR=/path/to/sfml/root ..
cmake --build .
```
