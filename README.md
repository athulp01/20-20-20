# 20-20-20
> For every 20 minutes spent using a screen; you should try to look away at something that is 20 feet away from you for a total of 20 seconds.

This program turns off your monitor after every 20 minutes for 20 seconds. It will sent a notification 1min before turning off the screen. User can also reset the 20min timer by a keypress.

# Dependencies
1. `notify-send` - for sending notifications.

# Installation
1. `make && make install`
2. `systemctl --user enable unstrain`
3. `systemctl --user start unstrain`
4. Create a keybinding to send SIGUSR1 to the process. (`kill -SIGUSR1 $(pgrep unstrain)`)
