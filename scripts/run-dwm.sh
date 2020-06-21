#! /usr/bin/env bash
# Helper for running dwm so that "exiting" dwm acts like a hot reload

while true; do
  # Log stderror to a file
  dwm 2> ~/.dwm.log
  # No error logging
  #dwm >/dev/null 2>&1
done
