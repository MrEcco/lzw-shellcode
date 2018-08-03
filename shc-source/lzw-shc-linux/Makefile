CC=gcc
CFLAGS=-c -Wall -O2
LDFLAGS=-Wl,-Map,mapfile
ARCH=$(shell ./arch-detect.sh)

all: lzw-decode.o my_mmap.o lzw-shc.o
	$(CC) $(LDFLAGS) lzw-decode.o my_mmap.o lzw-shc.o -o lzw-shc

lzw-decode.o: lzw-decode.c
	$(CC) $(CFLAGS) lzw-decode.c -o lzw-decode.o

my_mmap.o: my_mmap_x86_64.s my_mmap_i386.s
	$(CC) $(CFLAGS) my_mmap_$(ARCH).s -o my_mmap.o

lzw.o: lzw-shc.c
	$(CC) $(CFLAGS) lzw-shc.c -o lzw-shc.o

get-arch:
	echo $(ARCH)

clean:
	rm -rf *.o lzw-shc mapfile
