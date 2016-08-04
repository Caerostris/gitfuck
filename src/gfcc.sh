#!/bin/sh

set -e
RELATIVE_DIR=`dirname "${BASH_SOURCE[0]}"`
CCs="gcc clang"
GF2ASMs="gf2asm $RELATIVE_DIR/../bin/gf2asm"
 
for i in $CCs
do
	type -P "$i" &>/dev/null && CC="$i"
done

for i in $GF2ASMs
do
	type -P "$i" &>/dev/null && GF2ASM="$i"
done

if [ -z "$CC" ]; then
	echo "`basename \"$0\"` requires one of the following compilers: $CCs"
	exit 1
fi

if [ -z "$GF2ASM" ]; then
	echo "`basename \"$0\"`: error: could not find gf2asm"
	exit 1
fi

if [ -z "$1" ] || [ -z "$2" ]; then
	echo "`basename \"$0\"`: error: no input files"
	exit 1
fi

$GF2ASM "$1" "$1.tmp.s"
$CC "$1.tmp.s" -o "$2"
rm "$1.tmp.s"
