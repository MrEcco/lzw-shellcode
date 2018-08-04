Using
======================================
```C
size_t (*shc_func)(byte *, size_t, byte *);
shc_func = (size_t (*)(byte *, size_t, byte *))my_mmap(NULL, sizeof(shellcode), 
      PROT_EXEC | PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
memcpy(shc_func, shellcode, sizeof(shellcode));
out_size = shc_func(in, in_size, out);
my_munmap(shc_func, sizeof(shellcode));
```

Build guide
======================================
1) Just make

Test guide
======================================
```bash
openssl rand -out infile 102400
# Get and make lzw-tool from https://github.com/MrEcco/lzw-shellcode/tree/master/tool
#lzw -c -in infile -out infile.lzw
./lzw-shc
if [[ $(sha1sum infile | cut -d ' ' -f 1) == $(sha1sum outfile | cut -d ' ' -f 1) ]]
then
  echo SUCCESS!!!
else
  echo Something goes wrong... FAILED.
fi
rm infile infile.lzw outfile
```
