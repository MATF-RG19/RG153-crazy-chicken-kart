CXX=g++
CC=gcc
CFLAGS=-c
LDLIBS=-lglut -lGL -lGLU



PROGRAM=crazyChickenKart
OBJECTS=crazyChickenKart.o DrawFunctions.o 
all: $(PROGRAM)

$(PROGRAM): $(OBJECTS)
	$(CXX) -o $(PROGRAM) $(OBJECTS) $(LDLIBS) -lm

wolfQuest.o: crazyChickenKart.cpp
	$(CXX) $(CFLAGS) $(LDLIBS) crazyChickenKart.cpp 

drawFunc.o: DrawFunctions.cpp
	$(CXX) $(CFLAGS) $(LDLIBS) DrawFunctions.cpp

clean:
	rm -rf *o program