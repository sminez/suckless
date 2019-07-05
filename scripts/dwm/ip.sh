#!/bin/bash

INTERFACE=$(ip route | awk '/^default/ { print $5 ; exit }')
CURRENT_IP=$(ip route get 1 | cut -d' ' -f7)

if [[ "$(cat /sys/class/net/"$INTERFACE"/operstate)" = 'down' ]]; then
  echo -n  "ip: X"
else
  echo -n "$CURRENT_IP"
fi
