CC=g++
CFLAGS=-I./include/
DEPS = ./include/transaction.h ./ItemSelector.h
OBJ = pos.o transaction.o ItemSelector.o
FLCOMP=$(shell fltk-config --cxxflags)
FLLINK=$(shell fltk-config --ldflags)
OPTFLAGS=-O2

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) $(FLCOMP) $(OPTFLAGS)

pos: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(FLLINK)
