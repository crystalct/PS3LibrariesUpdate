#!/bin/sh -e
# cgcomp.sh by by CrystalCT (crystal@unict.it)

## Change directory
cd ../tools/cgcomp 

## Compile and install.
${MAKE:-make} install

## Copy cg.dll
cp  "$CG_BIN_PATH"/../bin.x64/cg.dll $PS3DEV/bin

