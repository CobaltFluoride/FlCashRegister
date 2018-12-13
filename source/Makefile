CC=g++
CFLAGS=-I./include/
DEPS = ./include/transaction.h
OBJ = pos.o transaction.o
FLCOMP=$(shell fltk-config --cxxflags)
FLLINK=$(shell fltk-config --ldflags)

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) $(FLCOMP) $(FLLINK)

pos: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(FLCOMP) $(FLLINK)
