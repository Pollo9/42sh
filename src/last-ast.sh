#!/bin/sh

shopt -s nullglob

for i in /tmp/42sh-ast-*.dot; do
	last="$i"
done
test "$last" || exit 1
echo "[$last] to [${last%*.dot}.png]"
dot -Tpng $last -o ${last%*.dot}.png
ln -sf ${last%*.dot}.png ast.png
