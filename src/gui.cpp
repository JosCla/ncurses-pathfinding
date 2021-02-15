// gui.cpp
// Implements gui.h

// C++ Standard Library
#include <algorithm>
using std::min;

// Libraries
#include <ncurses.h>

// Our Files
#include "gui.h"

GUI::GUI() {
	// Setting default values
	_windowsAllocated = false;
	_menuOpen = false;

	_titleWin = nullptr;
	_mapWin = nullptr;
	_menuWin = nullptr;
	_statusWin = nullptr;
}

GUI::GUI(WINDOW *cont) : GUI() {
	// Initializing windows
	initWindows(cont);
}

GUI::~GUI() {
	// Deallocating windows
	deallocateWindows();
}

void GUI::initWindows(WINDOW *cont) {
	// Deallocating windows if they have already been allocated
	if (_windowsAllocated) {
		deallocateWindows();
	}

	// Allocating all of the windows
	_titleWin = newwin(1, 1, 0, 0);
	_mapWin = newwin(1, 1, 0, 0);
	_menuWin = newwin(1, 1, 0, 0);
	_statusWin = newwin(1, 1, 0, 0);
	// (setting _windowsAllocated to true)
	_windowsAllocated = true;
	// (setting _contWin to cont)
	_contWin = cont;

	// Fitting the windows to a given container
	fitWindows();
}

void GUI::deallocateWindows() {
	// Deallocating windows
	if (_windowsAllocated) {
		delwin(_titleWin);
		_titleWin = nullptr;
		delwin(_mapWin);
		_mapWin = nullptr;
		delwin(_menuWin);
		_menuWin = nullptr;
		delwin(_statusWin);
		_statusWin = nullptr;

		_contWin = nullptr;
	}

	// (setting proper bool for window allocation)
	_windowsAllocated = false;
}

void GUI::fitWindows() {
	// Exiting if windows have not been initialized or if container is null
	if (!_windowsAllocated) {return;}
	if (_contWin == nullptr) {return;}

	// Finding container dimensions and position
	int maxY, maxX;
	getmaxyx(_contWin, maxY, maxX);
	int begY, begX;
	getbegyx(_contWin, begY, begX);

	// Making the title window (1 row at top)
	wresize(_titleWin, 1, maxX);
	mvwin(_titleWin, begY, begX);

	// Finding menu width
	int menuWidth;
	if (_menuOpen) {
		menuWidth = min(50, (maxX / 2));
	} else {
		menuWidth = 1;
	}

	// Making the menu window
	wresize(_menuWin, maxY - 2, menuWidth);
	mvwin(_menuWin, begY + 1, begX + maxX - menuWidth);

	// Making the map window
	wresize(_mapWin, maxY - 2, maxX - menuWidth);
	mvwin(_mapWin, begY + 1, begX);

	// Making the status window
	wresize(_statusWin, 1, maxX);
	mvwin(_statusWin, begY + maxY - 1, begX);	
}

void GUI::setContainer(WINDOW *cont) {
	_contWin = cont;
	fitWindows();
}
WINDOW* GUI::getContainer() {
	return _contWin;
}

void GUI::setMenuOpen(bool open) {
	_menuOpen = open;
	fitWindows();
}
bool GUI::getMenuOpen() {
	return _menuOpen;
}

WINDOW* GUI::getTitle() {
	return _titleWin;
}
WINDOW* GUI::getMap() {
	return _mapWin;
}
WINDOW* GUI::getMenu() {
	return _menuWin;
}
WINDOW* GUI::getStatus() {
	return _statusWin;
}

void GUI::boxAll() {
	// Returning if uninitialized
	if (!_windowsAllocated) {return;}

	// Putting boxes around all windows
	box(_titleWin, 0, 0);
	wrefresh(_titleWin);
	box(_mapWin, 0, 0);
	wrefresh(_mapWin);
	box(_menuWin, 0, 0);
	wrefresh(_menuWin);
	box(_statusWin, 0, 0);
	wrefresh(_statusWin);
}
