//  Philipp Siedler
//  Bjarne Stroustrup's PP
//  Chapter 16 Exercise 2

#define _USE_MATH_DEFINES
#include "Simple_window.h"
#include "Graph.h"
#include <cmath>
#include "GUI.h"

// layout
constexpr int xmax = 400;
constexpr int ymax = 400;

struct My_window : Window {
	My_window(Point xy, int w, int h, const string& title)
		: Window(xy, w, h, title),
		next_button_pushed(false),
		next_button(Point(x_max() - 140, 0), 70, 20, "Next", cb_next),
		quit_button_pushed(false),
		quit_button(Point(x_max() - 70, 0), 70, 20, "Quit", cb_quit)
	{
		attach(next_button);
		attach(quit_button);
	}

	void wait_for_button()
		// modified event loop
		// handle all events (as per default), but quit when button_pushed becomes true
		// this allows graphics without control inversion
	{
		while (!next_button_pushed) Fl::wait();
		next_button_pushed = false;
		Fl::redraw();
	}

	Button next_button;
	Button quit_button;

private:
	bool next_button_pushed;
	bool quit_button_pushed;

	static void cb_next(Address, Address addr) // callback for next_button
											   //	{ reference_to<Simple_window>(addr).next(); }
	{
		static_cast<My_window*>(addr)->next();
	}

	static void cb_quit(Address, Address addr) // callback for quit_button
											   //	{ reference_to<Simple_window>(addr).quit(); }
	{
		static_cast<My_window*>(addr)->quit();
	}

	void next() { next_button_pushed = true; }
	void quit() { hide(); }
};

struct cheker_board_buttons : My_window
{
	cheker_board_buttons(Point xy, int w, int h, const string& title)
		:My_window(xy, w, h, title)
	{
		int j = 0;
		for (int i = 0; i < 16; i++)
		{
			if (i % 4 == 0 && i != 0) { j++; }

			pressed.push_back(false);
			string label = "b";
			label += i;
			Button b(Point((xmax / 4) * (i % 4 + 1) - (xmax / 4), j * (ymax / 4) + 20), xmax / 4, ymax / 4, label, cb_change);
			buttons.push_back(b);
			attach(b);
		}
	}

	
	Vector_ref<Button> buttons;
	void change() { hide(); };

private:
	vector<bool> pressed;

	static void cb_change(Address, Address addr) // callback for quit_button
											   //	{ reference_to<Simple_window>(addr).quit(); }
	{
		static_cast<cheker_board_buttons*>(addr)->change();
	}

};

int main()
try
{
	cheker_board_buttons win(Point(100, 100), xmax, ymax + 20, "checker board buttons");
	return gui_main();
}
catch (exception& e) {
	cerr << "error: " << e.what() << '\n';
	keep_window_open();
	return 1;
}

catch (...) {
	cerr << "Unknown exception!\n";
	keep_window_open();
	return 2;
}