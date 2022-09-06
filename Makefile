all: 	main.o Game.o Component.o State.o Sprite.o Music.o GameObject.o Rect.o Vec2.o Sound.o TileSet.o TileMap.o Resources.o InputManager.o Camera.o NotCameraFollower.o Alien.o
	g++ -o main main.o Game.o Component.o State.o Sprite.o Music.o GameObject.o Rect.o Vec2.o Sound.o TileSet.o TileMap.o Resources.o InputManager.o Camera.o NotCameraFollower.o Alien.o -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
	rm -rf *.o

main.o: main.cpp 
	g++ -c main.cpp

Game.o: sources/Game.cpp
	g++ -c sources/Game.cpp

Component.o: sources/Component.cpp
	g++ -c sources/Component.cpp

State.o: sources/State.cpp
	g++ -c sources/State.cpp

Sprite.o: sources/Sprite.cpp
	g++ -c sources/Sprite.cpp

Music.o: sources/Music.cpp
	g++ -c sources/Music.cpp

GameObject.o: sources/GameObject.cpp
	g++ -c sources/GameObject.cpp

# Face.o: sources/Face.cpp
# 	g++ -c sources/Face.cpp

Rect.o: sources/Rect.cpp
	g++ -c sources/Rect.cpp

Vec2.o: sources/Vec2.cpp
	g++ -c sources/Vec2.cpp

Sound.o: sources/Sound.cpp
	g++ -c sources/Sound.cpp

TileSet.o: sources/TileSet.cpp
	g++ -c sources/TileSet.cpp

TileMap.o: sources/TileMap.cpp
	g++ -c sources/TileMap.cpp

Resources.o: sources/Resources.cpp
	g++ -c sources/Resources.cpp

InputManager.o: sources/InputManager.cpp
	g++ -c sources/InputManager.cpp

Camera.o: sources/Camera.cpp
	g++ -c sources/Camera.cpp

NotCameraFollower.o: sources/NotCameraFollower.cpp
	g++ -c sources/NotCameraFollower.cpp

Alien.o: sources/Alien.cpp
	g++ -c sources/Alien.cpp

run:
	./main




