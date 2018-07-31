LZW compress-decompress tool
=====================================
```
Usage: lzw [ -c | -e | -d ] [ -in infile.bin ] [ -out outfile.bin ]
   -h          - show this help
   -c          - compress (by default)
   -e          - compress(same as '-c')
   -d          - decompress
   -in <file>  - input file
   -out <file> - output file
```
Compatibility
------------------------------------
LZW tool is compat with WinNT 5+ if builded without msvcr*.dll dependencies, and with Linux 2.6+ kernel.

Compilation guide
====================================
Windows
------------------------------------
For build tool for windows we are use Visual Studio with special settings:<br>
1) C\C++ -> Common -> SDL Checks = Disable <br>
2) C\C++ -> Preprocessor -> Set definitions for preprocessos:
```C
#define __WINDOWS__
```
3) Dont use precompiled headers

Linux
------------------------------------
Just use makefile
