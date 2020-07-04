#!/bin/sh -e

# Automatic build script for polarssl
# for psl1ght, playstaion 3 open source sdk.
#
# Originally Created by Felix Schulze on 08.04.11.
# Ported to PS3Libraries to compile with psl1ght.
# Copyright 2010 Felix Schulze. All rights reserved.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
###########################################################################
# Change values here https://tls.mbed.org/download/mbedtls-2.1.0-gpl.tgz
#
VERSION="1.3.22"
#
###########################################################################
#
# Don't change anything here
CURRENTPATH=`pwd`
ARCH="powerpc64"
PLATFORM="PS3"

## Download the source code.
wget --continue --no-check-certificate -O mbedtls-${VERSION}.gpl.tgz  https://tls.mbed.org/download/mbedtls-${VERSION}-gpl.tgz?do=yes

## Unpack the source code.
rm -Rf mbedtls-${VERSION} && tar xfvz mbedtls-${VERSION}.gpl.tgz && cd mbedtls-${VERSION}

## Patch the source code.
echo "Patching net.c, timing.c and config.h for compatibility..."
cd include
cat ../../../patches/mbedtls-1.3.9-config.patch | patch -p1
cd ../library
cat ../../../patches/polarssl-1.2.8-net.patch | patch -p1
cat ../../../patches/polarssl-1.3.22-timing.patch | patch -p1


echo "Building mbedtls for ${PLATFORM} ${SDKVERSION} ${ARCH}"

echo "Patching Makefile..."
sed -i.bak '4d' ${CURRENTPATH}/mbedtls-${VERSION}/library/Makefile

echo "Please stand by..."

export CC=$PS3DEV/ppu/bin/powerpc64-ps3-elf-gcc
export LD=$PS3DEV/ppu/bin/powerpc64-ps3-elf-ld
export CPP=$PS3DEV/ppu/bin/powerpc64-ps3-elf-cpp
export CXX=$PS3DEV/ppu/bin/powerpc64-ps3-elf-g++
export AR=$PS3DEV/ppu/bin/powerpc64-ps3-elf-ar
export AS=$PS3DEV/ppu/bin/powerpc64-ps3-elf-as
export NM=$PS3DEV/ppu/bin/powerpc64-ps3-elf-nm
export CXXCPP=$PS3DEV/ppu/bin/powerpc64-ps3-elf-cpp
export RANLIB=$PS3DEV/ppu/bin/powerpc64-ps3-elf-ranlib
export LDFLAGS="-L$PS3DEV/ppu/powerpc64-ps3-elf/lib -L$PSL1GHT/ppu/lib -L$PS3DEV/portlibs/ppu/lib -lrt -llv2"
export CFLAGS="-I${CURRENTPATH}/mbedtls-${VERSION}/include -I$PS3DEV/ppu/powerpc64-ps3-elf/include -I$PSL1GHT/ppu/include -I$PS3DEV/portlibs/ppu/include -mcpu=cell"

echo "Build library..."
## Compile and install.
${MAKE:-make}

cp libmbedtls.a $PS3DEV/portlibs/ppu/lib/libmbedtls.a
cp libmbedtls.a $PS3DEV/portlibs/ppu/lib/libpolarssl.a
cp -R ../include/polarssl $PS3DEV/portlibs/ppu/include/
cp ../LICENSE $PS3DEV/portlibs/ppu/include/polarssl/LICENSE

echo "Building done."
