#!/bin/bash

if [ $# -ne 1 ]; then
  echo "Было введено $# аргументов. Нужен только 1 аргумент"
  exit 1
fi

if [ ! -d "$1" ]; then
  echo "$1 - не существует или не является директорией"
  exit 1
fi

start=$(cd "$1" && pwd)


walk() {
  local dir="$1"
  local item

  for item in "$dir"/*; do
    [ -e "$item" ] || continue

    if [ -d "$item" ]; then
      echo "$item"
      walk "$item"
    fi
  done
}

walk "$start"
