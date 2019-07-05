#!/bin/bash

PENDING_SYMBOL=" "

read upgraded new removed held < <(
    # Grab the update info
    aptitude full-upgrade --simulate --assume-yes |
    # Find the line that states what changes are pending
    grep -m1 '^[0-9]\+ packages upgraded' |
    # Pull of the counts in each section and return as a single space delimited line
    awk ' BEGIN { RS=",|and"; ORS=" " }; { print $1 }'
)
echo -n "$PENDING_SYMBOL$upgraded/$new/$removed/$held"
