# Homework #2
## Compile
### Build
```
make
```

### Clean
```
make clean
```

## Usage

```
./hw2 [-a] [-x] [-p | -q | -r | -s] [-t]
```
By default, the program lists only the processes belong to the current user and have an associated terminal.


#### Options

* `-a` option can be used to list processes from all the users.
* `-x` option can be used to list processes without an associated terminal
* `-p`, `-q`, `-r`, and `-s`, options can be used to sort the listed processes by pid (default), ppid, pgid, and sid, respectively.
* `-t` option can be used to list processes in a tree-relationship, just like pstree.

#### Example Output
```
  pid   uid   gid  ppid  pgid   sid      tty St (img) cmd
 1307  1000  1000  1280  1307  1307     tty2  S (gdm-x-session) /usr/lib/gdm3/gdm-x-session
 1309  1000  1000  1307  1307  1307     tty2  S (Xorg) /usr/lib/xorg/Xorg
 1318  1000  1000  1307  1307  1307     tty2  S (gnome-session-b) /usr/lib/gnome-session/gnome-session-binary
 1450  1000  1000  1318  1307  1307     tty2  S (gnome-shell) /usr/bin/gnome-shell
 1472  1000  1000  1450  1472  1307     tty2  S (ibus-daemon) ibus-daemon
 1476  1000  1000  1472  1472  1307     tty2  S (ibus-dconf) /usr/lib/ibus/ibus-dconf
 1478  1000  1000     1  1472  1307     tty2  S (ibus-x11) /usr/lib/ibus/ibus-x11
 1543  1000  1000  1318  1307  1307     tty2  S (gsd-power) /usr/lib/gnome-settings-daemon/gsd-power
 1546  1000  1000  1318  1307  1307     tty2  S (gsd-print-notif) /usr/lib/gnome-settings-daemon/gsd-print-notifications
 1549  1000  1000  1318  1307  1307     tty2  S (gsd-rfkill) /usr/lib/gnome-settings-daemon/gsd-rfkill
 1550  1000  1000  1318  1307  1307     tty2  S (gsd-screensaver) /usr/lib/gnome-settings-daemon/gsd-screensaver-proxy
 1551  1000  1000  1318  1307  1307     tty2  S (gsd-sharing) /usr/lib/gnome-settings-daemon/gsd-sharing
 1554  1000  1000  1318  1307  1307     tty2  S (gsd-xsettings) /usr/lib/gnome-settings-daemon/gsd-xsettings
 1566  1000  1000  1318  1307  1307     tty2  S (gsd-smartcard) /usr/lib/gnome-settings-daemon/gsd-smartcard
 1570  1000  1000  1318  1307  1307     tty2  S (gsd-sound) /usr/lib/gnome-settings-daemon/gsd-sound
 1571  1000  1000  1318  1307  1307     tty2  S (gsd-wacom) /usr/lib/gnome-settings-daemon/gsd-wacom
 1575  1000  1000  1318  1307  1307     tty2  S (gsd-a11y-settin) /usr/lib/gnome-settings-daemon/gsd-a11y-settings
 1578  1000  1000  1318  1307  1307     tty2  S (gsd-clipboard) /usr/lib/gnome-settings-daemon/gsd-clipboard
 1582  1000  1000  1318  1307  1307     tty2  S (gsd-color) /usr/lib/gnome-settings-daemon/gsd-color
 1586  1000  1000  1318  1307  1307     tty2  S (gsd-datetime) /usr/lib/gnome-settings-daemon/gsd-datetime
 1587  1000  1000  1318  1307  1307     tty2  S (gsd-housekeepin) /usr/lib/gnome-settings-daemon/gsd-housekeeping
 1591  1000  1000  1318  1307  1307     tty2  S (gsd-keyboard) /usr/lib/gnome-settings-daemon/gsd-keyboard
 1592  1000  1000  1318  1307  1307     tty2  S (gsd-media-keys) /usr/lib/gnome-settings-daemon/gsd-media-keys
 1593  1000  1000  1318  1307  1307     tty2  S (gsd-mouse) /usr/lib/gnome-settings-daemon/gsd-mouse
 1611  1000  1000     1  1307  1307     tty2  S (gsd-printer) /usr/lib/gnome-settings-daemon/gsd-printer
 1643  1000  1000  1318  1307  1307     tty2  S (gnome-software) /usr/bin/gnome-software
 1644  1000  1000  1318  1307  1307     tty2  S (nautilus-deskto) nautilus-desktop
 1645  1000  1000  1318  1307  1307     tty2  S (gsd-disk-utilit) /usr/lib/gnome-disk-utility/gsd-disk-utility-notify
 1650  1000  1000     1  1307  1307     tty2  S (vmtoolsd) /usr/bin/vmtoolsd
 1713  1000  1000  1472  1472  1307     tty2  S (ibus-engine-sim) /usr/lib/ibus/ibus-engine-simple
 1833  1000  1000  1318  1307  1307     tty2  S (update-notifier) update-notifier
 1849  1000  1000  1318  1307  1307     tty2  S (deja-dup-monito) /usr/lib/deja-dup/deja-dup-monitor
 1876  1000  1000  1866  1876  1876    pts/0  S (bash) bash
 1892  1000  1000  1876  1892  1876    pts/0  S (make) make
 1909  1000  1000  1892  1892  1876    pts/0  R (hw2) ./hw2

```
