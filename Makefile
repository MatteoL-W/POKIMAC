# $@ pour nom de cible
# $< pour nom de la premiere dependance
# $^ pour toute la liste des dépendances

# *****************************************************
# Variables

CC=g++
CXXFLAGS=-Wall
IFOLDER=include
SFOLDER=src
BFOLDER=build

ifeq ($(OS),Windows_NT)
    CXXFLAGS=-Wall
    SDLFLAGS=-lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf
    RM = del
    MKDIR = -mkdir
    SEP=\\
else
	# BE AWARE ! WE COULDN'T CHECK IF THIS WORKS FOR LINUX / MAC ! SORRY
    CXXFLAGS = -Wall -O2 -g
    SDLFLAGS = -lSDL2 -lGLU -lGL -lm -lSDL2_image -lSDL2_ttf
    RM = rm -rf 
    MKDIR = mkdir -p
    SEP=\/
endif

# _____________________________________________________



# *****************************************************
# Make

render: build/main.o build/Utils.o build/Game.o build/StarterInterface.o build/ExplorationInterface.o build/AttackInterface.o build/InventoryInterface.o build/EndingInterface.o build/Starter.o build/Map.o build/Pokemon.o build/Text.o build/Battle.o build/Inventory.o build/Ending.o
	$(CC) -o bin/$@ $^ $(SDLFLAGS)

$(BFOLDER)/%.o: $(SFOLDER)/%.cpp $(IFOLDER)/%.hpp
	$(CC) -o $@ -c $< $(CXXFLAGS)

# _____________________________________________________



# *****************************************************
# Commands

clean:
	$(RM) build$(SEP)*.o

st:
	./bin/render

init:
	$(MKDIR) build;
	$(MKDIR) bin;

# _____________________________________________________