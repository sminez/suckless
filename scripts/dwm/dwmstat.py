#!/usr/bin/python3.7
"""
A simple status generator intended for use with dwm.

Supports segments running python code or alternatively calling out to a
shell script.
"""
import time
import subprocess

SCRIPT_DIR = "/home/innes/bin/scripts/dwm"


def run(cmd, raw=False):
    """Run a shell command"""
    if not raw:
        cmd = f"{SCRIPT_DIR}/{cmd}"

    def _cmd():
        res = subprocess.run(cmd.split(), stdout=subprocess.PIPE)
        return res.stdout.decode()

    return _cmd


class Segment:
    """
    A segment that updates state every `interval` seconds
    """
    def __init__(self, cmd=None, interval=1):
        self.interval = interval
        self.cmd = cmd
        self._last_tick = 0
        self._state = ""

    def update(self, tick):
        """Update the state if we ticked."""
        if tick < self._last_tick + self.interval:
            return

        self._state = self.cmd()
        self._last_tick = tick

    def __str__(self):
        return self._state


SEGMENTS = [
    Segment(run("ip.sh"), 60),
    Segment(run("current-wifi-access-point.sh"), 60),
    Segment(run("wifi.sh"), 60),
    Segment(run("bat.sh"), 60),
    Segment(run("vol.sh"), 1),
    Segment(run("kb.sh"), 1),
    Segment(time.ctime, 1),
]

while True:
    for seg in SEGMENTS:
        seg.update(int(time.time()))

    STATUS = " " + "  ".join(str(s) for s in SEGMENTS)
    subprocess.run(["xsetroot", "-name", STATUS])
    time.sleep(1)
