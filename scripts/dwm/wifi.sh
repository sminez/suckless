#!/bin/bash

INTERFACE=$(ip route | awk '/^default/ { print $5 ; exit }')
QUALITY=$(grep "$INTERFACE" /proc/net/wireless | awk '{ print int($3 * 100 / 70) }')

[[ ! -d /sys/class/net/${INTERFACE}/wireless ]] ||
    [[ "$(cat /sys/class/net/$INTERFACE/operstate)" = 'down' ]] && exit

# wifi signal bars
if [[ $QUALITY -ge 80 ]]; then
  graph="$(/home/innes/bin/spark 0 1 2 3 4)"
elif [[ $QUALITY -lt 80 ]]; then
  graph="$(/home/innes/bin/spark 0 1 2 3 0)"
elif [[ $QUALITY -lt 60 ]]; then
  graph="$(/home/innes/bin/spark 0 1 2 0 0)"
elif [[ $QUALITY -lt 40 ]]; then
  graph="$(/home/innes/bin/spark 0 1 0 0 0)"
fi

echo -n "$graph "
