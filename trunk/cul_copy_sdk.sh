#!/bin/sh

source="."
destination=""

static="libcul.a"
shared="libcul.so{,.*}"

if [ -z "$1" ]; then
	echo "No destination parameter"
	echo "Usage: $0 <destination>"
	exit -1
fi

# copy destination
destination="$1"

if [ "$destination" == "$source" ]; then
	echo "Source and destination have to be different!"
	exit -1
fi

sourceLib="$source/.cmake/lib"
sourceConfig="$source/.cmake/cul"
sourceInclude="$source/include/cul"

if [ ! -d "$sourceLib" ] || [ ! -d "$sourceConfig" ];  then
	echo "Library not commpiled"
	exit -1
fi

if [ ! -d "$sourceInclude" ]; then
	echo "Include files not present"
	exit -1
fi

libIn=`ls "$sourceLib"/libcul{.a,.so,.so.*} 2>/dev/null`
includeIn=`ls "$sourceInclude"/*.h`
includeConfigIn=`ls "$sourceConfig"/*.h`

libPresent="false"
for lib in $libIn; do
	if [ -f "$lib" ]; then
		libPresent="true"
		break
	fi
done

if [ ! "$libPresent" == "true" ]; then
	echo "No shared or static library present"
	exit -1
fi

destinationLib="$destination/lib"
destinationInclude="$destination/include/cul"

# create output directories
mkdir -p "$destinationLib"
mkdir -p "$destinationInclude"

# clean output directiories
rm -f "$destinationLib"/libcul{.a,.so,.so.*}
rm -f "$destinationInclude"/*.h

# copy libraries (perserve symlinks)
for file in $libIn; do
	cp -P "$file" "$destinationLib"
done

# copy includes
for file in $includeIn; do
	cp "$file" "$destinationInclude"
done

# copy config
for file in $includeConfigIn; do
	cp "$file" "$destinationInclude"
done

echo "Cul library sdk copied!"
