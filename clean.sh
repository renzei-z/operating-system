#!/bin/sh

set -e
. ./config.sh

for PROJECT in $PROJECTS; do
  (cd $PROJECT && $MAKE clean)
done

rm -rf root
rm -rf isodir
rm -rf sillyos.iso
