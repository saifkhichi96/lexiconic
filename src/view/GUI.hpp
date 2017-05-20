#ifndef GUI_HPP
#define GUI_HPP

#include "../../libs/include/SmartGL/SmartGL.h"
#include "../entity/Dictionary.h"
#include "../entity/Date.hpp"

// Global data shared across files
const int BACKSPACE = 8;				// ASCII value of Backspace key, used in KeyboardEvents() methods
const int ENTER = 13;					// ASCII value of Enter key, used in KeyboardEvents() methods
extern Dictionary wordList;				// Main dictionary object, defined in main.cpp
extern Dictionary userDictionary;		// User dictionary object, defined in main.cpp


/*
GUI defines the basic user interface of the application. It is an abstract class, which
extends the Activity abstract class from SmartGL graphics library. SmartGL is an extension
of OpenGL Utility Toolkit (GLUT). All 'activities' in this application will extend the GUI
class.
*/
class GUI : public Activity
{
public:
			GUI();									// Default public constructor.
	virtual ~GUI() = 0;								// Pure virtual destructor to make the class abstract.
	void	Display();								// Defines the layout of the activity.
	void	MouseEvents(int&, int&, int&, int&);	// Defines programs behaviour on mouse events.

protected:
	string	activeButton;							// ID of the button which is currently active
	bool	showSidebar;							// Flag to indicate if the sidebar is shown or hidden

private:
	void	createSidebar();

	static Texture* images;							// These images (textures) will be shared across each activity
	static void	loadTextures();						// and will be loaded only once.
};

#endif


#ifndef SPLASH_HPP
#define SPLASH_HPP

class Splash : public Activity
{
public:
			Splash();								// Default public constructor.
	void	Display();								// Defines the layout of the activity.

private:
	float	progress;								// Loading progress
};

#endif


#ifndef ABOUT_HPP
#define ABOUT_HPP

class About : public GUI
{
public:
			About();								// Default public constructor.
	void	Display();								// Defines the layout of the activity.
	void	MouseEvents(int&, int&, int&, int&);	// Defines programs behaviour on mouse events.
};

#endif