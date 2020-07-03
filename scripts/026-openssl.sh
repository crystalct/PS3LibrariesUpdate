#!/bin/sh -e

# Automatic build script for openssl
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
# Modified by CrystalCT (crystal@unict.it) - July 2020
###########################################################################
# Change values here
#
VERSION="1.1.1"
REV="g"
#
###########################################################################
#
# Don't change anything here
CURRENTPATH=`pwd`
ARCH="powerpc64"
PLATFORM="PS3"

VERPATH=${VERSION}
if [ $(echo ${VERPATH} | grep '^0' | wc -l) -eq 1 ]; then
	VERPATH="0.9.x"
fi

VERSION="${VERSION}${REV}"

## Download the source code.
wget --continue --no-check-certificate -O openssl-${VERSION}.tar.gz https://www.openssl.org/source/openssl-${VERSION}.tar.gz
wgetchk=$?

if [ ${wgetchk} -ne 0 ]; then
	# probably archived
	wget --continue --no-check-certificate -O openssl-${VERSION}.tar.gz https://www.openssl.org/source/$VERSION/openssl-${VERSION}.tar.gz
fi

# No longer need $VERSION and $REV seperate


## Unpack the source code.
rm -Rf openssl-${VERSION} && tar xfvz openssl-${VERSION}.tar.gz && cd openssl-${VERSION}

echo "Building openssl for ${PLATFORM} ${SDKVERSION} ${ARCH}"

echo "Please stand by..."

#patch -p1 < ../../patches/openssl-1.1.0i-OSSL_SSIZE_MAX.patch
patch -p1 < ../../patches/openssl-1.1.0i-memory_h.patch
patch Configurations/10-main.conf ../../patches/openssl-1.1.1g-CNF_EX_LIBS.patch

export PREFIX=${PS3DEV}/portlibs/ppu
#export CC=${PS3DEV}/ppu/bin/powerpc64-ps3-elf-gcc
#export LD=${PS3DEV}/ppu/bin/powerpc64-ps3-elf-ld
#export CPP=${PS3DEV}/ppu/bin/powerpc64-ps3-elf-cpp
#export CXX=${PS3DEV}/ppu/bin/powerpc64-ps3-elf-g++
#export AR=${PS3DEV}/ppu/bin/powerpc64-ps3-elf-ar
#export AS=${PS3DEV}/ppu/bin/powerpc64-ps3-elf-as
#export NM=${PS3DEV}/ppu/bin/powerpc64-ps3-elf-nm
#export CXXCPP=${PS3DEV}/ppu/bin/powerpc64-ps3-elf-cpp
#export RANLIB=${PS3DEV}/ppu/bin/powerpc64-ps3-elf-ranlib
export LDFLAGS="-L${PS3DEV}/ppu/powerpc64-ps3-elf/lib -L${PSL1GHT}/ppu/lib -L${PREFIX}/lib -lrt -llv2"
export CFLAGS="-I${CURRENTPATH}/openssl-${VERSION}/include -I${PS3DEV}/ppu/powerpc64-ps3-elf/include -I${PSL1GHT}/ppu/include -I${PREFIX}/include -mcpu=cell"
./Configure linux-ppc64 -DNO_SYSLOG \
--prefix="${PREFIX}" --openssldir="${PREFIX}" --cross-compile-prefix=${PS3DEV}/ppu/bin/powerpc64-ps3-elf- \
-static no-shared no-asm no-hw no-engine no-threads no-sock no-dso \
no-cms no-capieng no-ui enable-weak-ssl-ciphers no-autoalginit \
no-autoerrinit no-err no-filenames no-hw-padlock no-rdrand \
no-posix-io no-stdio \
${CFLAGS} ${LDFLAGS}

echo "Build library..."
## Compile and install.
#{MAKE:-make} depends
#${MAKE:-make} include/openssl/opensslconf.h
#${MAKE:-make} crypto/include/internal/bn_conf.h
#${MAKE:-make} crypto/include/internal/dso_conf.h
#${MAKE:-make} -j4 libcrypto.a

#cp libssl.a ${PS3DEV}/portlibs/ppu/lib/libssl.a
#cp libcrypto.a ${PS3DEV}/portlibs/ppu/lib/libcrypto.a
#cp -R include/openssl ${PS3DEV}/portlibs/ppu/include/
#cp LICENSE ${PS3DEV}/portlibs/ppu/include/openssl/LICENSE

${MAKE:-make} -j4
${MAKE:-make} install
echo "Building done."
