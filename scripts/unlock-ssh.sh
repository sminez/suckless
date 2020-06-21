#! /usr/bin/env bash
# Unlock my RSA key. Called on startup
output=$(echo | SSH_ASKPASS=~/bin/scripts/unlock-ssh-helper.sh ssh-add 2>&1)
notify-send "SSH Unlock Output" "$output"
