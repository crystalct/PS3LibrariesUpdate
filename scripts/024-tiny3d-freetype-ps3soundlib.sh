#!/bin/sh -e
# tiny3D_soundlib.sh by Hermes - Estwald - [CrystalCT 2020 Update]

## Download the source code.
wget --no-check-certificate https://github.com/crystalct/tiny3D_ps3soundlib/tarball/master -O tiny3D_soundlib.tar.gz 

## Unpack the source code.
rm -Rf tiny3D_soundlib && mkdir tiny3D_soundlib && tar --strip-components=1 --directory=tiny3D_soundlib -xvzf tiny3D_soundlib.tar.gz && cd tiny3D_soundlib

## Compile and install.
${MAKE:-make} all

## Copy samples to $PS3SRC/samples/tiny3D
mkdir -p $PS3SRC/samples/tiny3D
mkdir -p $PS3SRC/samples/PSL1GHT

cp -frv samples/* $PS3SRC/samples/tiny3D
cp -frv PSL1GHT.samples/* $PS3SRC/samples/PSL1GHT
echo Samples copied to $PS3SRC/samples/PSL1GHT and $PS3SRC/samples/tiny3D
