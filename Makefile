CC=g++ -std=c++11 -g
EXE_FILE=r

all: $(EXE_FILE)

$(EXE_FILE): event.o bats.o wumpus.o room.o gold.o pits.o game.o event.h bats.h wumpus.h room.h gold.h pits.h game.h driver.cpp
	$(CC) event.o bats.o wumpus.o room.o gold.o pits.o game.o driver.cpp -o $(EXE_FILE)

event.o: event.h event.cpp
	$(CC) -c event.cpp
	
bats.o: bats.h bats.cpp
	$(CC) -c bats.cpp

wumpus.o: wumpus.h wumpus.cpp
	$(CC) -c wumpus.cpp
	
room.o: room.h room.cpp
	$(CC) -c room.cpp
	
gold.o: gold.h gold.cpp
	$(CC) -c gold.cpp

pits.o: pits.h pits.cpp
	$(CC) -c pits.cpp

game.o: game.h game.cpp
	$(CC) -c game.cpp


clean:
	rm -f *.o $(EXE_FILE)

