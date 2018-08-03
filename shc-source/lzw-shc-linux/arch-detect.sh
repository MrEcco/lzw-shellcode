#!/bin/bash
if [[ $(echo $MACHTYPE | sed "s/-.*//g; s/i[0-9]*86/iXXX86/g") == "iXXX86" ]]
then
  echo -e "i386"
fi
if [[ $(echo $MACHTYPE | sed "s/-.*//g") == "x86_64" ]]
then
  echo -e "x86_64"
fi
