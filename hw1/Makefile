CXX = g++
CXXFLAGS = -I. -Wall -static -O2

all: cmd.o main.o
	$(CXX) -o hw1 cmd.o main.o $(CXXFLAGS)

%.o: %.cpp
	$(CXX) -c $< $(CXXFLAGS)

.PHONY: run clean

clean:
	rm -rf hw1 *.o

run: all
	./main

