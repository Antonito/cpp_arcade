#!/bin/bash

echo -n "Linking intefaces ..."
for file in ./deps/interface/*
do
    if [[ -f $file ]]; then
	name=$(echo "$file" | rev | cut -d '/' -f 1 | rev)
	src="../../deps/interface/""$name"
	target="$name"
	cd ./common/src/
	cp -f "$src" "$target" > /dev/null
	cd - > /dev/null;
    fi
done
echo " OK"
