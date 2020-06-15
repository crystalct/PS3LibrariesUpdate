#!/bin/sh -e
# jpeg-9d.sh by CrystalCT (crystal@unict.it)

## Download the source code.
wget --continue http://www.ijg.org/files/jpegsrc.v9d.tar.gz

## Download an up-to-date config.guess and config.sub
if [ ! -f config.guess ]; then wget --continue http://git.savannah.gnu.org/cgit/config.git/plain/config.guess; fi
if [ ! -f config.sub ]; then wget --continue http://git.savannah.gnu.org/cgit/config.git/plain/config.sub; fi

## Unpack the source code.
rm -Rf jpeg-9d && tar xfvz jpegsrc.v9d.tar.gz && cd jpeg-9d

## Replace config.guess and config.sub
cp ../config.guess ../config.sub .


## Create the build directory.
mkdir build-ppu && cd build-ppu

## Configure the build.
CFLAGS="-I$PSL1GHT/ppu/include -I$PS3DEV/portlibs/ppu/include -O2" \
CPPFLAGS="-I$PSL1GHT/ppu/include -I$PS3DEV/portlibs/ppu/include -O2" \
LDFLAGS="-L$PSL1GHT/ppu/lib -L$PS3DEV/portlibs/ppu/lib -lrt -llv2" \
PKG_CONFIG_PATH="$PS3DEV/portlibs/ppu/lib/pkgconfig" \
../configure --prefix="$PS3DEV/portlibs/ppu" --host="powerpc64-ps3-elf" --disable-shared

## Compile and install.
${MAKE:-make} -j4 && ${MAKE:-make} install