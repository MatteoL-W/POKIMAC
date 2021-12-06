# $@ pour nom de cible
# $< pour nom de la premiere dependance
# $^ pour toute la liste des dépendances

# *****************************************************
# Variables

CC=g++
CFLAGS=-Wall
SDLFLAGS=-lmingw32 -lSDL2main -lSDL2
IFOLDER=include
SFOLDER=src

ifeq ($(OS),Windows_NT)
    RM = del
    MKDIR = -mkdir
	SEP=\\
else
    RM = rm -rf 
    MKDIR = mkdir -p
	SEP=\/
endif

# _____________________________________________________



# *****************************************************
# Make

#TODO: remplacez les build par $^
render: main.o game.o maths.o utils.o graphics.o
	$(CC) -o bin/$@ build/main.o build/game.o build/maths.o build/utils.o build/graphics.o $(SDLFLAGS)

main.o: $(SFOLDER)/main.cpp $(IFOLDER)/main.hpp
	$(CC) -o build/$@ -c $< $(CFLAGS)

game.o: $(SFOLDER)/game.cpp $(IFOLDER)/game.hpp
	$(CC) -o build/$@ -c $< $(CFLAGS)

maths.o: $(SFOLDER)/maths.cpp $(IFOLDER)/maths.hpp
	$(CC) -o build/$@ -c $< $(CFLAGS)

utils.o: $(SFOLDER)/utils.cpp $(IFOLDER)/utils.hpp
	$(CC) -o build/$@ -c $< $(CFLAGS)

graphics.o: $(SFOLDER)/graphics.cpp $(IFOLDER)/graphics.hpp
	$(CC) -o build/$@ -c $< $(CFLAGS)

# _____________________________________________________



# *****************************************************
# Commands

clean:
	$(RM) build$(SEP)*.o

st:
	./bin/render.exe

init:
	mkdir build;
	mkdir bin;

# _____________________________________________________