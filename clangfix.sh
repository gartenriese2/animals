#!/bin/sh

sed -i "$(cat <<EOF
/ifndef \(CC\|CXX\)/{
N
N
s/.*\n *\(.*\)\n *endif *$/\1/}
EOF
)" build/Makefile
