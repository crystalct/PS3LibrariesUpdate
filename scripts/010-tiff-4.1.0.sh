#!/bin/sh -e
# tiff-4.1.0.sh by CrystalCT <crystal@unict.it>

## Download the source code.
wget --continue http://download.osgeo.org/libtiff/tiff-4.1.0.tar.gz

## Download an up-to-date config.guess and config.sub
if [ ! -f config.guess ]; then wget --continue http://git.savannah.gnu.org/cgit/config.git/plain/config.guess; fi
if [ ! -f config.sub ]; then wget --continue http://git.savannah.gnu.org/cgit/config.git/plain/config.sub; fi

## Unpack the source code.
rm -Rf tiff-4.1.0 && tar xfvz ./tiff-4.1.0.tar.gz && cd tiff-4.1.0

## Replace config.guess and config.sub
cp ../config.guess ../config.sub config/

## Patch the source code.
patch contrib/iptcutil/iptcutil.c ../../../patches/iptcutil.patch

## Create the build directory.
mkdir build-ppu && cd build-ppu

## Configure the build.
CFLAGS="-I$PSL1GHT/ppu/include -I$PS3DEV/portlibs/ppu/include" \
LDFLAGS="-L$PSL1GHT/ppu/lib -L$PS3DEV/portlibs/ppu/lib -lrt -llv2" \
PKG_CONFIG_PATH="$PS3DEV/portlibs/ppu/lib/pkgconfig" \
../configure --prefix="$PS3DEV/portlibs/ppu" --host="powerpc64-ps3-elf" --disable-shared

## Compile and install.
${MAKE:-make} && ${MAKE:-make} install
