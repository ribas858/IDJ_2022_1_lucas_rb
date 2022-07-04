all: 	main.o Game.o State.o Sprite.o Music.o
	g++ -o main main.o Game.o State.o Sprite.o Music.o -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
	rm -rf *.o

main.o: main.cpp 
	g++ -c main.cpp

Game.o: sources/Game.cpp
	g++ -c sources/Game.cpp

State.o: sources/State.cpp
	g++ -c sources/State.cpp

Sprite.o: sources/Sprite.cpp
	g++ -c sources/Sprite.cpp

Music.o: sources/Music.cpp
	g++ -c sources/Music.cpp

run:
	./main




