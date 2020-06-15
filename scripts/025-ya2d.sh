#!/bin/sh -e
# libya2d.sh by Xerpi (xerpi.g.12@gmail.com) - Bucanero (www.bucanero.com.ar) 2020 Update

## Download the source code.
wget --no-check-certificate https://github.com/bucanero/ya2d_ps3/tarball/master -O ya2d_ps3.tar.gz 

## Unpack the source code.
rm -Rf ya2d_ps3 && mkdir ya2d_ps3 && tar --strip-components=1 --directory=ya2d_ps3 -xvzf ya2d_ps3.tar.gz && cd ya2d_ps3/libya2d

## Compile and install.
${MAKE:-make} install

## Copy samples to $PS3SRC/samples/ya2d
mkdir -p $PS3SRC/samples/ya2d

cp -frv ../sample/* $PS3SRC/samples/ya2d
echo Samples copied to $PS3SRC/samples/ya2d
