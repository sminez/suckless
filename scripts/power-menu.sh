#!/bin/bash
#----------
# Launch a dmenu based power menu.

selection=$(
  echo -e "lock\nlogout\nshutdown\nreboot\nsuspend\nhibernate" |
  dmenu -p "What would you like to do? " -l 10
)

case "$selection" in
       lock) xautolock -locknow;;
     logout) pkill dwm;;
   shutdown) sudo shutdown -h now &;;
     reboot) sudo reboot;;
    suspend) sudo pm-suspend && xautolock -locknow;;
  hibernate) sudo pm-hibernate && xautolock -locknow;;
esac
