#!/usr/bin/bash
INCLUDED_FILES=""
expand() {
    file="$1"
    abs_path=$(realpath "$file")
    case "$INCLUDED_FILES" in
        *"$abs_path"*) return ;;
    esac
    INCLUDED_FILES="$INCLUDED_FILES
$abs_path"
    while IFS= read -r line; do
        case "$line" in
            \#include\<bits/*\>        | \
            \#include\<atcoder/*\>     | \
            \#include\<all.h\>         | \
            \#include[[:space:]]\<bits/*\>    | \
            \#include[[:space:]]\<atcoder/*\> | \
            \#include[[:space:]]\<all.h\>)
                echo "$line"
                ;;
            \#include[[:space:]]\<*[\>] | \
            \#include\<*[\>])
                tmp="${line#*<}"
                inc_path="${tmp%%>*}"
                real_path="./lib/src/$inc_path"
                if [ -f "$real_path" ]; then
                    expand "$real_path"
                else
                    echo "$line"
                fi
                ;;
            \#pragma[[:space:]]once)
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
