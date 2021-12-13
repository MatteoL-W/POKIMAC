# $@ pour nom de cible
# $< pour nom de la premiere dependance
# $^ pour toute la liste des dépendances

# *****************************************************
# Variables

CC=g++
CXXFLAGS=-Wall
SDLFLAGS=-lmingw32 -lSDL2main -lSDL2 -lSDL2_image
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
#%.o : %.cpp
#	   g++ -c $< 
render: main.o Game.o maths.o utils.o graphics.o
	$(CC) -o bin/$@ build/main.o build/Game.o build/maths.o build/utils.o build/graphics.o $(SDLFLAGS)

%.o: $(SFOLDER)/%.cpp $(IFOLDER)/%.hpp
	$(CC) -o build/$@ -c $< $(CXXFLAGS)

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

#TODO: mettre SDL dans le lib/