#!/bin/bash
layout=$(setxkbmap -verbose 10 | awk -F':' '/layout/ { print $2 }' | xargs)
echo -n "[$layout]"

