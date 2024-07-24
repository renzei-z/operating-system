#!/bin/sh

set -e
. ./iso.sh

qemu-system-$(./target_to_arch.sh $TARGET) -cdrom sillyos.iso
