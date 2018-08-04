#!/bin/bash
openssl rand -base64 -out infile 1024000
TEST1=$(sha1sum ./infile | cut -d ' ' -f 1)
./lzw -e -in infile -out infile.lzw &>/dev/null
./lzw -d -in infile.lzw -out outfile &>/dev/null
TEST2=$(sha1sum ./outfile | cut -d ' ' -f 1)
rm infile infile.lzw outfile
if [[ $TEST1 == $TEST2 ]]
then
  echo SUCCESS!!!
else
  echo FAILED
fi
