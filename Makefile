CXX=g++ 
CC=gcc
CFLAGS=-c 
LDLIBS=-lglut -lGL -lGLU -lm
OPTS =  -I"irrKlang/include" -L"/usr/lib" irrKlang/bin/linux-gcc-64/libIrrKlang.so -pthread


PROGRAM=crazyChickenKart
OBJECTS=crazyChickenKart.o DrawFunctions.o  image.o



all: $(PROGRAM)

$(PROGRAM): $(OBJECTS)
	$(CXX) -o $(PROGRAM) $(OBJECTS) $(LDLIBS) $(OPTS)

crazyChickenKart.o: crazyChickenKart.cpp
	$(CXX) -g $(CFLAGS) $(LDLIBS) crazyChickenKart.cpp 

drawFunc.o: DrawFunctions.cpp
	$(CXX) -g $(CFLAGS) $(LDLIBS) DrawFunctions.cpp

image.o: Textures/image.cpp
	$(CXX) -g $(CFLAGS) $(LDLIBS) Textures/image.cpp



clean:
	rm -rf *o program
