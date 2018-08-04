CPP=g++
CPPFLAGS=-c -Wall -O2
CC=gcc
CFLAGS=-c -Wall -O2
ARCH=$(shell ./arch-detect.sh)

all: lzw

lzw: lzw.o lzw_c.o my_mmap.o
	$(CPP) lzw.o lzw_c.o my_mmap.o -o lzw

lzw.o: lzw.cpp
	$(CPP) $(CPPFLAGS) lzw.cpp

lzw_c.o: lzw_c.c
	$(CC) $(CFLAGS) lzw_c.c

my_mmap.o: my_mmap_x86_64.s my_mmap_i386.s
	$(CC) $(CFLAGS) my_mmap_$(ARCH).s -o my_mmap.o

test:
	$(value $(shell ./test.sh))

clean:
	rm -rf *.o lzw
