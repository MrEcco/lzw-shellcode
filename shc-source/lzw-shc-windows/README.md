Shellcode
==========================
```C
byte shellcode[] = { ... }; // See https://github.com/MrEcco/lzw-shellcode/blob/master/shellcode_windows_x64.c
                            // or  https://github.com/MrEcco/lzw-shellcode/blob/master/shellcode_windows_x32.c
size_t(*shc_func)(byte*, size_t, byte*);
byte * in, * out;
size_t in_size, out_size;

shc_func = (size_t(*)(byte*, size_t, byte*))VirtualAlloc(NULL, sizeof(shellcode), MEM_COMMIT, PAGE_EXECUTE_READWRITE);
memcpy(shc_func, shellcode, sizeof(shellcode));
out_size = shc_func(in, in_size, out);
VirtualFree(shc_func, 0, MEM_RELEASE);
```
Build shellcode
==========================
Stage 1 - Get hashs
--------------------------
First we need compute "special hash of some functions", which defined in _HASH_*_ directives.
1. Uncomment definition _JUST_GET_HASHS_. If this is active - other functions has been stripped. 
2. Compile and run exe. Copy output and insert gotten hashs to shellcode_factory region.
3. Comment definition _JUST_GET_HASHS_.

Stage 2 - Testing exe
--------------------------
Second stage is build and test app.
1. Undefine _JUST_GET_HASHS_ and _OVER_SHELLCODE_ if it isnt do before.
2. Compile.
3. Now we need compressend file for tests. Just select "the somefile" bigger than 100Kb and compress it with
my tool https://github.com/MrEcco/lzw-shellcode/tree/master/tool . Copy output filename to definition 
_FILENAME_INPUT_ and set any other _FILENAME_OUTPUT_.
4. Test exe. It must read _FILENAME_INPUT_ and decompress it to _FILENAME_OUTPUT_. If sha1 of "the somefile" 
and _FILENAME_OUTPUT_ is equal then test is success.

Stage 3 - Extract shellcode
--------------------------
Now we can start to extract shellcode. Be carefull, it stage have different ways for different archs.
1. Open mapfile in folder with source code. Look at the table with RVA of compiled functions.
```
 <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< CUTED >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 Address             Publics by Value              Rva+Base               Lib:Object
 <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< CUTED >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 0000:00000000       __ImageBase                   0000000140000000     <linker-defined>
 0001:00000000       ?lzw_decode@@YA_KPEAE_K0@Z    0000000140001000 f   lzw-shc-windows.obj
 0001:0000036c       ?getProcAddrByHash@@YAPEAXK@Z 000000014000136c f   lzw-shc-windows.obj
 0001:00000470       __local_stdio_printf_options  0000000140001470 f i lzw-shc-windows.obj
 0001:00000478       fprintf                       0000000140001478 f i lzw-shc-windows.obj
 0001:000004bc       main                          00000001400014bc f   lzw-shc-windows.obj
 0001:00000690       getPEB                        0000000140001690 f   getpeb_x64.obj
 0001:0000069a       getEIP                        000000014000169a f   getpeb_x64.obj
 0001:000008f8       mainCRTStartup                00000001400018f8 f   MSVCRT:exe_main.obj
 <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< CUTED >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
```
2. Compute size of first mashine code block. It must be _lzw_decode_ and _getProcAddrByHash_ in row: <br>
RVA(___local_stdio_printf_options_) - RVA(_lzw_decode_) = 0x0140001470 - 0x0140001000 = 0x470
Now we know:
```
First block:
RVA:  0x0140001000
Size: 0x470
```
3. This round need only for x86_64 architecture. If you build exe for x86 - go to next round.<br>
Compute size of second (last) mashine code block. It must be _getPEB_: <br>
RVA(_getEIP_) - RVA(_getPEB_) = 0x014000169a - 0x0140001690 = 0x0a
Now we know:
```
Second block:
RVA:  0x0140001690
Size: 0x0a
```
4. Open exe in debugger. Static or dynamic - isnt matter. I prefer x32dbg or x64dbg.
5. Enter to _lzw_decode_ function and just copy only FIRST_BLOCK_SIZE (0x470, 1136 in decimal) bytes of mashine 
code since start of _lzw_decode_. This is content of first block.
6. This round need only for x86_64 architecture. If you build exe for x86 - go to next round.<br>
Enter to _getPEB_ function and just copy onlu SECOND_BLOCK_SIZE (0x0a, 10 in decimal) bytes of mashine code 
since start og _getPEB_. This is content of second block.
7. For x86:<br>
First block is all of shellcode. No additional actions need. Use it like in code below. <br>
For x86_64:
    1. Just concat first and second blocks.
  	2. Now need change call instruction in code of first block. Restart debugger and set breakpoint to start of _getPEB_.
  	For each break on this point check call trace and find out which call instruction refer to _getPEB_. Get it RVA(s). I found only one.
  	3. Find offset of this calls from start of _lzw_decode_:<br>
  	RVA(CALL_INCRUCTION) - RVA(_lzw_decode_) = 0x387
  	4. Look at inctuction:
  	```
  	0000000140001387        E8 04 03 00 00      call <lzw-shc-windows.getPEB>
  	```
  	5. It is call function from offset 0x304 (dot forgot about little-endian). We need change it to second 
  	block. Compute how far _getPEB_ was moved:<br>
  	RVA(_getPEB_) - RVA(__local_stdio_printf_options) = 0x0140001690 - 0x0140001470 = 0x220
  	6. Compute new call offset: <br>
  	ORIG_CALL_OFFSET - HOW_FAR_MOVED = 0x304 - 0x220 = 0xE4
  	7. Insert new call offset in mashine code. Find "E8 04 03 00 00" in 0x387 byte of concatenated blocks and change it 
  	to "E8 E4 00 00 00".
  	8. Complite! Now you have x86_64 shellcode for windows.

Stage 4 - Testing shellcode
------------------------------------
1. Uncomment _OVER_SHELLCODE_ definition.
2. Insert your new shellcode to code (find out "byte shellcode[] = " and replace content of variable).
3. Compile and test workability.
