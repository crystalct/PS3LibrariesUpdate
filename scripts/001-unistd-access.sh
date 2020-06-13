#!/bin/sh -e
# unistd-access.sh by CrystalCT (crystal@unict.it)

## Compile source code.
powerpc64-ps3-elf-gcc -I$PSL1GHT/ppu/include -c ../src/access.c

## Add access.o to librt.a
powerpc64-ps3-elf-ar -rsv $PSL1GHT/ppu/lib/librt.a access.o

## Remove access.o.
rm access.o

