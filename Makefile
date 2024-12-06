all: game

game: game.c
	gcc -o game game.c -pthread

clean:
	rm -f game