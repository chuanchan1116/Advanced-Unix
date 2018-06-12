CXX = g++
CXXFLAGS = -Wall -O2

all: main.o
	$(CXX) $(CXXFLAGS) -o lanchat $^

%.o: %.c
	$(CXX) $(CXXFLAGS) -c $<

.PHONY: run clean

run: all
	sudo ./lanchat

clean:
	rm lanchat main.o
