CPP=g++
CPPFLAGS=-c -Wall
CC=gcc
CFLAGS=-c -Wall

all: lzw

lzw: lzw.o lzw_c.o
        $(CPP) lzw.o lzw_c.o -o lzw

lzw.o: lzw.cpp
        $(CPP) $(CPPFLAGS) lzw.cpp

lzw_c.o: lzw_c.c
        $(CC) $(CFLAGS) lzw_c.c

clean:
        rm -rf *.o lzw
