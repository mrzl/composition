//
// Created by mar on 14.08.17.
//

#include <X11/Xlib.h>
#include <cstdio>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <iostream>

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/input.h>
#include <fcntl.h>
#include <cstring>
#include "mouse_listener.h"


void query_pointer(Window& root, Display *d)
{
	int i, x, y;
	unsigned m;
	Window w;

	root = DefaultRootWindow(d);

	if (!XQueryPointer(d, root, &root, &w, &x, &y, &i, &i, &m)) {
		for (i = -1; ++i < ScreenCount(d); ) {
			if (root == RootWindow(d, i)) {
				break;
			}
		}
	}
	Screen*  scrn = DefaultScreenOfDisplay(d);
	int height = scrn->height;
	int width  = scrn->width;
	//std::cout << "W: " << width << " H: " << height << std::endl;
	//std::cout << "X: " << x << " Y: " << y << std::endl;
}

void SendPressKeyEvent(Display *display, XKeyEvent xkey)
{
	Window current_focus_window;
	int current_focus_revert;
	XGetInputFocus(display, &current_focus_window, &current_focus_revert);
	xkey.type =  KeyPress;
	xkey.display = display;
	xkey.window = current_focus_window;
	xkey.root = DefaultRootWindow(display);
	xkey.subwindow = None;
	xkey.time = 1000 * time(0);
	xkey.x = 0;
	xkey.y = 0;
	xkey.x_root = 0;
	xkey.y_root = 0;
	xkey.same_screen = True;
	XSendEvent(display, InputFocus,  True, KeyPressMask, (XEvent *)(&xkey));
}

void SendReleaseKeyEvent(Display *display, XKeyEvent xkey)
{
	Window current_focus_window;
	int current_focus_revert;
	XGetInputFocus(display, &current_focus_window, &current_focus_revert);
	xkey.type =  KeyRelease;
	xkey.display = display;
	xkey.window = current_focus_window;
	xkey.root = DefaultRootWindow(display);
	xkey.subwindow = None;
	xkey.time = 1000 * time(0);
	xkey.x = 0;
	xkey.y = 0;
	xkey.x_root = 0;
	xkey.y_root = 0;
	xkey.same_screen = True;
	XSendEvent(display, InputFocus, True, KeyReleaseMask, (XEvent *)(&xkey));
}
/*
void *TaskCode(void* arg)
{
	switch(*(int*)arg)
	{
		case 38:
			system("espeak -v en "  "\"a\"");
	}
	return 0;
}

int main(void)
{
	XSetWindowAttributes attribs;
	Window root;
	Display* d;
	Window w;

	if (!(d = XOpenDisplay(0))) {
		std::cout << "Couldn't connect to " << XDisplayName (nullptr) << std::endl;
		exit (EXIT_FAILURE);
	}

	attribs.override_redirect = True;
	w = XCreateWindow(d, DefaultRootWindow (d), -1, -1, 1, 1, 0,
					  CopyFromParent, InputOnly, CopyFromParent,
					  CWOverrideRedirect, &attribs);
	XMapWindow(d, w);
	XSync (d, 0);

	while(true) {
		query_pointer(root, d);
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}
*/

/*
int main(int argc, char** argv)
{
    int fd, bytes;
    unsigned char data[3];

    const char *pDevice = "/dev/input/mice";

    // Open Mouse
    fd = open(pDevice, O_RDWR);
    if(fd == -1)
    {
        printf("ERROR Opening %s\n", pDevice);
        return -1;
    }

    int left, middle, right;
    signed char x, y;
    while(1)
    {
        // Read Mouse
        bytes = read(fd, data, sizeof(data));

        if(bytes > 0)
        {
            left = data[0] & 0x1;
            right = data[0] & 0x2;
            middle = data[0] & 0x4;

            x = data[1];
            y = data[2];
            printf("x=%d, y=%d, left=%d, middle=%d, right=%d\n", x, y, left, middle, right);
        }
    }
    return 0;
}
*/

int main(void)
{
	mouse_listener listener;
	listener.start();

	for(int i = 0; i < 20; i++)
	{
		std::cout << "x: " << listener.x() << " y: " << listener.y() << " w: " << listener.w() << " h: " << listener.h() << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(5));
	}

	listener.stop();
}
