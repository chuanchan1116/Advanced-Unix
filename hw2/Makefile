CC = gcc
CFLAGS = -Wall -O2 -s -Os

all: main.o ps.o devname.o readproc.o
	$(CC) $(CFLAGS) -o hw2 $^

%.o: %.c
	$(CC) $(CFLAGS) -c $<

.PHONY: run clean

clean:
	rm hw2 *.o

run: all
	./hw2
