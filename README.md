# Pong++ by LordPaijo

This is a repository about my stupid ahh game of pong made in C++ using the library, [`Raylib`](https://github.com/raysan5/raylib).

## Raylib
This game is made using [`Raylib`](https://github.com/raysan5/raylib).
### Installation
A full installation guide is available [here](https://github.com/raysan5/raylib?tab=readme-ov-file#),

or use these links
######### [GNU / LINUX](https://github.com/raysan5/raylib/wiki/Working-on-GNU-Linux)
######### [WINDOWS](https://github.com/raysan5/raylib/wiki/Working-on-Windows) 
######### [MAC-OS / OS-X](https://github.com/raysan5/raylib/wiki/Working-on-macOS)

## Compiling the game
```bash
git clone https://github.com/berakpaijo/Pong-Raylib.git Pong++
cd Pong++
g++ main.cpp -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -o game
```
## Running the game
You can run the game by executing the one you have compiled, or by executing the already compiled one in `/output/`
```bash
./game            #  your compiled file
./output/game     #  already included compiled file in /output/
```
