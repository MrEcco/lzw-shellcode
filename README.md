# lzw-shellcode
Decompress shellcode for x32/x64 Windows and Linux and tools for pack/unpack payload

This project is ,in particular, just demonstration of how to work with heap from shellcode, and totatly, is example for develop any  shellcode for any architecture.

LZW isnt high compression rate, but have tiny code and enouth for deliver small parts of remote mashine code.

Take no responsibility. The author refuses any liability that may arise as a result of using this code, regardless of who used it.

# Using guide
## Windows
```C
size_t(*shc_func)(byte*, size_t, byte*);
shc_func = (size_t(*)(byte*, size_t, byte*))VirtualAlloc(NULL, sizeof(shellcode), 
      MEM_COMMIT, PAGE_EXECUTE_READWRITE);
memcpy(shc_func, shellcode, sizeof(shellcode));
out_size = shc_func(in, in_size, out);
VirtualFree(shc_func, 0, MEM_RELEASE);
```
## Linux
```C
size_t (*shc_func)(byte *, size_t, byte *);
shc_func = (size_t (*)(byte *, size_t, byte *))mmap(NULL, sizeof(shellcode), 
      PROT_EXEC | PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
memcpy(shc_func, shellcode, sizeof(shellcode));
out_size = shc_func(in, in_size, out);
munmap(shc_func, sizeof(shellcode));
```

# AV-detection
Isnt susceptible for static analisis on 04.08.2018.<br>
Eazy detect any payload after decompress.
# repa tyt