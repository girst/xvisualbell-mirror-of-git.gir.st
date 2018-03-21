/* briefly flashes a fullscreen white window to simulate a visual bell */
#define _DEFAULT_SOURCE
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <unistd.h>

int main (int argc, char** argv) {
	Display *display;
	Window  window;
	XWindowAttributes xwa;
	XSetWindowAttributes xswa;
	unsigned long bgcolor = 0xffffff;

	/* parse command line arguments for 3bit colors */
	if (argc > 1) switch(argv[1][0]) {
		case 'r': bgcolor = 0xff0000; break;
		case 'g': bgcolor = 0x00ff00; break;
		case 'b': bgcolor = 0x0000ff; break;
		case 'c': bgcolor = 0x00ffff; break;
		case 'm': bgcolor = 0xff00ff; break;
		case 'y': bgcolor = 0xffff00; break;
		case 'k': bgcolor = 0x000000; break;
		case 'w': bgcolor = 0xffffff; break;
	}

	display = XOpenDisplay(NULL);

	/* indirectly aquire display resolution through root window's size*/
	XGetWindowAttributes(display, XDefaultRootWindow(display), &xwa);

	window = XCreateSimpleWindow (display, XDefaultRootWindow(display),
		0, 0, /* position left/top */
		xwa.width, xwa.height,
		0, 0, /* border settings */
		bgcolor);

	/*shut out window manager (makes window full screen over all monitors)*/
	xswa.override_redirect = 1;
	XChangeWindowAttributes (display, window, CWOverrideRedirect, &xswa);

	XMapWindow(display,window);
	XFlush(display);

	usleep(100000);
	return 0;
}
