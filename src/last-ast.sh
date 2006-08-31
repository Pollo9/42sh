#!/bin/sh

for i in /tmp/42sh-ast-*.dot; do
	last="$i"
done

echo "$last to echo x${last%*.dot}"
dot -Tpng $last -o ${last%*.dot}.png
ln -sf ${last%*.dot}.png ast.png
