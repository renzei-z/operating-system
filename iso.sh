#!/bin/sh

set -e
. ./build.sh

mkdir -p isodir/boot/grub

cp root/boot/sillyos.kernel isodir/boot/sillyos.kernel
cat > isodir/boot/grub/grub.cfg << EOF
menuentry "sillyos" {
  multiboot /boot/sillyos.kernel
}
EOF
grub-mkrescue -o sillyos.iso isodir
