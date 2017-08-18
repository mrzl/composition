//
// Created by mar on 18.08.17.
//

#pragma once

#include <X11/Xlib.h>
#include <atomic>
#include <thread>

class mouse_listener {
public:
	mouse_listener();
	~mouse_listener();

	void start();
	void stop();

	void mouse_button_callback( std::function<void()> &callback );

	int x() const;
	int y() const;
	int w() const;
	int h() const;

private:
	Window root;
	Display* display;

	std::atomic<int> m_mouse_x, m_mouse_y, m_screen_width, m_screen_height;
	std::thread m_mouse_position_thread;
	std::atomic<bool> m_running;

	int m_mouse_file;
	const std::string m_mouse_button_file_name = "/dev/input/mice";
	std::thread m_mouse_button_pressed_thread;
	std::function<void()> m_mouse_click_callback;
	std::atomic<int> m_mouse_pressed_left, m_mouse_pressed_middle, m_mouse_pressed_right;

	void query_pointer( Window &root, Display* d );
};
