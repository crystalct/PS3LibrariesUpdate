#!/bin/sh -e
# fp.sh by by CrystalCT (crystal@unict.it)

## Change directory
cd ../tools/toolshaderf

## Compile and install.
${MAKE:-make} install

## Copy samples to $PS3SRC/samples/fp
mkdir -p $PS3SRC/samples/fp
cp -frv samples/* $PS3SRC/samples/fp

