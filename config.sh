SYSTEM_HEADER_PROJECTS="libc kernel"
PROJECTS="libc kernel"

export MAKE=${MAKE:-make}
export TARGET=${TARGET:-$($(dirname $0)/echo-default-target.sh)}

export AR=${TARGET}-ar
export AS=${TARGET}-as
export CC=${TARGET}-gcc

export PREFIX=/usr
export EXEC_PREFIX=$PREFIX
export BOOTDIR=/boot
export LIBDIR=$EXEC_PREFIX/lib
export INCLUDEDIR=$EXEC_PREFIX/include

export CFLAGS='-O2 -g'
export CPPFLAGS=''

export SYSROOT="$(pwd)/root"
export CC="$CC --sysroot=$SYSROOT"
export NASM="nasm"

if echo "$TARGET" | grep -Eq -- '-elf($|-)'; then
  export CC="$CC -isystem=$INCLUDEDIR"
fi

