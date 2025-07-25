#!/bin/sh

INCLUDED_FILES=""

expand() {
	file="$1"
	abs_path=$(realpath "$file")

	# guard
	if echo "$INCLUDED_FILES" | grep -qFx "$abs_path"; then
		return
	fi
	INCLUDED_FILES="$INCLUDED_FILES
$abs_path"

	while IFS= read -r line; do
		case "$line" in
			\#include[\ \	]*\<bits/*\>|\
\#include[\ \	]*\<atcoder/*\>|\
\#include[\ \	]*\<all.h\>)
				# bits/ と atcoder/ はスルー
				echo "$line"
				;;
			\#include[\ \	]*\<*\>) 
				# ./libから
				inc_path=$(echo "$line" | sed -n 's/#include[[:space:]]*<\([^>]*\)>/\1/p')
				real_path="./lib/src/$inc_path"
				if [ -f "$real_path" ]; then
					expand "$real_path"
				else
					echo "$line"
				fi
				;;
			\#pragma[\ \	]*once)
				# #pragma once は出力しない
				;;
			*)
				echo "$line"
				;;
		esac
	done < "$file"
}

if [ $# -ne 1 ]; then
	echo "Usage: $0 filename" >&2
	exit 1
fi

expand "$1"

