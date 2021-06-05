#include <X11/Xlib.h>
#include <X11/extensions/dpms.h>
#include <err.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

unsigned short is_reset;

static void set_screen_state(unsigned short state) {
  Display *dpy;
  if (!(dpy = XOpenDisplay(0)))
    errx(1, "cannot open display '%s'", XDisplayName(0));
  DPMSEnable(dpy);
  if (state)
    DPMSForceLevel(dpy, DPMSModeOn);
  else
    DPMSForceLevel(dpy, DPMSModeOff);
  XSync(dpy, False);
  return;
}

static void reset() {
  if (is_reset) {
    is_reset = 0;
    system("notify-send \"Timer reset\" -u normal -t 1000");
  }
}

//Turn off screen after every timeout seconds for interval seconds;
//timeout and interval are in seconds
static void lock(unsigned int timeout, unsigned int interval) {
  sleep(timeout - 60);
  reset(); //signal will wake this sleep, if user presses the key
  system("notify-send \"Screen will be turned off in 1 minute. Pass SIGUSR1 to "
         "reset the timer\" -u normal -t 5000");
  sleep(60);
  reset();
  set_screen_state(0);
  sleep(interval);
  set_screen_state(1);
  reset();
  return;
}


static void handle_sigusr1(int sig) {
  is_reset = 1;
  return;
}

int main() {
  signal(SIGUSR1, handle_sigusr1);
  while (1) {
    lock(1200, 20);
  }
}
