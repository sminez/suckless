#!/bin/bash

instance="BAT0"
bat_stats=$(upower -i /org/freedesktop/UPower/devices/battery_$instance |
    sed -e "s/ //g" |
    awk -F: 'BEGIN { ORS=" " }; /state|percentage/ { print $2 }')
state=$(echo "$bat_stats" | cut -d" " -f1)
percentage=$(echo "$bat_stats" | cut -d" " -f2 | sed -e "s/%//g")

# Icon to indicate the current charge
if [[ "$state" == "charging" ]]; then
    label=""
elif [[ "$percentage" == 100 ]]; then
    label=""
elif [[ "$percentage" -gt 99 ]]; then
    label=""
elif [[ "$percentage" -gt 75 ]]; then
    label=""
elif [[ "$percentage" -gt 50 ]]; then
    label=""
elif [[ "$percentage" -gt 25 ]]; then
    label=""
elif [[ "$percentage" -gt 10 ]]; then
    label=""
else
    label=""
fi

echo -n "$label $percentage%"
