all: 	main.o Game.o Component.o State.o Sprite.o Music.o GameObject.o Face.o Rect.o Vec2.o
	g++ -o main main.o Game.o Component.o State.o Sprite.o Music.o GameObject.o Face.o Rect.o Vec2.o -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
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

Face.o: sources/Face.cpp
	g++ -c sources/Face.cpp

Rect.o: sources/Rect.cpp
	g++ -c sources/Rect.cpp

Vec2.o: sources/Vec2.cpp
	g++ -c sources/Vec2.cpp


run:
	./main




