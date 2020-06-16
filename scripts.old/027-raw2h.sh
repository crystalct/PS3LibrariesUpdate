#!/bin/sh -e
# cgcomp.sh by by CrystalCT (crystal@unict.it)

## Change directory
cd ../tools/raw2h

## Compile and install.
${MAKE:-make} install

