#! /usr/bin/env bash
# -------------------------------------
# Bootstrap the start of a dwm session
# >> This get's run on restart as well!
# -------------------------------------

# Make sure we only run once
pid=$$
pgrep -fi start-dwm.sh | grep -v "^$pid$" | xargs kill

# Set screen resolutions (add additional screens here)
# xrandr --output eDP-1 --mode 1920x1080 &
# xrandr --output HDMI-2 --auto --right-of eDP-1 &

# Fix stupid Java apps that fail without a WMNAME to look for...
wmname LG3D

pgrep -fi 'dwmstat.zsh' | xargs kill
"$HOME/bin/scripts/dwmstat.zsh" &

running() { pgrep -fi "$1" >/dev/null; }

running picom || picom &  # -cf --backend xr_glx_hybrid --vsync opengl --xrender-sync-fence --vsync-aggressive --xrender-sync -m .9 &
running nm-applet || nm-applet &
running udiskie || udiskie -a -n -t &
running xautolock || xautolock -detectsleep -time 3 -locker "/home/innes/bin/lock-screen"  -notify 30 -notifier "notify-send -u critical -t 10000 -- 'LOCKING screen in 30 seconds...'" &
running volumeicon || volumeicon &
running dunst || dunst &
running xfce4-power-manager || xfce4-power-manager &
running gnome-keyring-daemon || gnome-keyring-daemon --start --components=pkcs11,secrets,ssh &

feh --bg-fill "$HOME/Pictures/wallpapers/cookie.jpg" &
"$HOME/bin/unlock-ssh.sh" &
