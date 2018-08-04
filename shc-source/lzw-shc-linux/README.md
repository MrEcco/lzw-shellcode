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
