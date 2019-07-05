#!/bin/bash
# -------------------------------------
# Bootsrap the start of a qtile session
# >> This get's run on restart as well!
# -------------------------------------

# pgrep -x doesn't seem to work for this. No idea why...
# This is used to make sure that things only get executed once
is_running() {
    ps -aux | awk "!/grep/ && /$1/"
}

# Make sure we only run once
pid=$$
kill $(pgrep -x start-dwm.sh | grep -v ^$pid$)

# Set screen resolutions (add additional screens here)
# xrandr --output eDP-1 --mode 1920x1080 &
xrandr --output HDMI-2 --auto --right-of eDP-1 &

# Fix stupid Java apps that fail without a WMNAME to look for...
wmname LG3D

pkill dwmstat.py
/home/innes/bin/scripts/dwm/dwmstat.py &

# Set the background image
feh --bg-fill /home/innes/Pictures/wallpapers/leaves.jpg &

# Eye candy
[[ $(is_running 'compton') ]] || compton &  # -cf --backend xr_glx_hybrid --vsync opengl --xrender-sync-fence --vsync-aggressive --xrender-sync -m .9 &
# Network manager
[[ $(is_running 'nm-applet') ]] || nm-applet &
# Auto-mount external drives
[[ $(is_running 'udiskie') ]] || udiskie -a -n -t &
# Start xautolock using my wrapper around i3lock
# NOTE :: lock-screen is my custom screen lock script in ~/bin
[[ $(is_running 'xautolock') ]] || xautolock -detectsleep -time 3 -locker "/home/innes/bin/lock-screen"  -notify 30 -notifier "notify-send -u critical -t 10000 -- 'LOCKING screen in 30 seconds...'" &
# Notification daemon : first kill the default mate daemon if it has spun up
[[ $(is_running 'dunst') ]] || dunst &
# Music server
[[ $(is_running 'mopidy') ]] || python2 -m mopidy &

[[ $(is_running 'clipnotify') ]] || clipnotify &
[[ $(is_running 'clipmenud') ]] || clipmenud &

unlock-ssh.sh &
