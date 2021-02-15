#ifndef GUI_H
#define GUI_H
// gui.h
// Provides and manages a graphical user interface

// Libraries
#include <ncurses.h>

class GUI {
public:
	// Constructors/Destructors
	GUI();
	GUI(WINDOW *cont);
	~GUI();

	// Initializes all of the windows
	void initWindows(WINDOW *cont = stdscr);
	void deallocateWindows();
	// Fits all of the windows to their container
	void fitWindows();

	// Getter/setter for window container
	void setContainer(WINDOW *cont);
	WINDOW* getContainer();

	// Getter/setter for _menuOpen
	void setMenuOpen(bool open);
	bool getMenuOpen();

	// Getters for all window pointers
	WINDOW* getTitle();
	WINDOW* getMap();
	WINDOW* getMenu();
	WINDOW* getStatus();

	// Extra function for putting a box around all windows!
	void boxAll();

private:
	// Window pointers
	WINDOW *_titleWin;
	WINDOW *_mapWin;
	WINDOW *_menuWin;
	WINDOW *_statusWin;
	WINDOW *_contWin; // pointer to container window
	bool _windowsAllocated; // whether or not windows have been allocated

	// Bool for whether or not the menu is open
	bool _menuOpen;
};

#endif // GUI_H
