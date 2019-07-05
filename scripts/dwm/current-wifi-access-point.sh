#!/bin/bash
AP=$(nmcli | grep 'connected to' | cut -d' ' -f4)
INTERFACE=$(ip route | awk '/^default/ { print $5 ; exit }')
QUALITY=$(grep "$INTERFACE" /proc/net/wireless | awk '{ print int($3 * 100 / 70) }')

echo -n "$AP"
