#ifndef _MY_MMAP_H_
#define _MY_MMAP_H_

#include <stdint.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <syscall.h>

extern void * my_mmap(void * addr, size_t length, int prot, int flags, int fd, off_t offset);
extern int my_munmap(void * addr, size_t length);

#endif
