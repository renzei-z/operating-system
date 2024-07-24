#!/bin/sh
#
# This script transforms the target (e.g. i386-elf, x86_64-elf)
# to the corresponding architecture string (i386, x86_64).

if echo "$1" | grep -Eq 'i[[:digit:]]86-'; then
  echo i386
else
  echo "$1" | grep -Eo '^[[:alnum:]_]*'
fi
