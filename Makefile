# $@ pour nom de cible
# $< pour nom de la premiere dependance
# $^ pour toute la liste des dépendances

# *****************************************************
# Variables

CC=g++
CXXFLAGS=-Wall
SDLFLAGS=-lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf
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
render: main.o Utils.o Game.o StarterInterface.o ExplorationInterface.o AttackInterface.o InventoryInterface.o EndingInterface.o Starter.o Map.o Pokemon.o Text.o Battle.o Inventory.o Ending.o
	$(CC) -o bin/$@ build/main.o build/Utils.o build/Game.o build/StarterInterface.o build/ExplorationInterface.o build/AttackInterface.o build/InventoryInterface.o build/EndingInterface.o build/Starter.o build/Map.o build/Pokemon.o build/Text.o build/Battle.o build/Inventory.o build/Ending.o  $(SDLFLAGS)

%.o: $(SFOLDER)/%.cpp $(IFOLDER)/%.hpp
	$(CC) -o build/$@ -c $< $(CXXFLAGS)

# _____________________________________________________



# *****************************************************
# Commands

clean:
	$(RM) build$(SEP)*.o

st:
	./bin/render

init:
	mkdir build;
	mkdir bin;

# _____________________________________________________