#!/bin/bash
vol="$(amixer get Master | tail -n1 | sed -r 's/.*\[(.*)%\].*/\1/')"
if test "$vol" -gt 0
then
    echo -n -e "vol: ${vol}%"
else
    echo -n -e "vol: X"
fi

