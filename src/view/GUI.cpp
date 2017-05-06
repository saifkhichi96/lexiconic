#include "GUI.hpp"

Texture *GUI::images = NULL;

GUI::GUI()
	: activeButton("NULL"), showSidebar(false)
{
	/*
	Default public constructor for the GUI class. It loads images and creates
	othere user interface elements that will be shared across different activities
	in this application
	*/
	
	loadTextures();
	createSidebar();
}

GUI::~GUI()
{
	/*
	This is a pure virtual method whose only purpose is to make this class abstract. However,
	since it is a destructor, it has to be defined, albeit having no implementation.
	*/
}

void GUI::Display()
{
	/*
	Display() method overrides a super class method. It defines the UI layout which will
	be used across all the activities in this application.
	*/

	if (!showSidebar)
	{
		// Menu button (onClick() -> show sidebar)
		getButton("UI_0").Display();

		// Active button -> the action bar button on which mouse
		// is currently hovering (if any)
		if (activeButton != "NULL")
			getButton(activeButton).Display();
	}
	else
	{
		// Show sidebar background
		textures.get("Sidebar").Display();

		// Show sidebar buttons
		for (int i = 1; i <= 6; i++)
		{
			string id = "UI_" + to_string(i);
			getButton(id).Display();
		}
	}
}

void GUI::MouseEvents(int& button, int& state, int& x, int& y)
{
	/*
	MouseEvents() method overrides a super class method and is used to specify how the program
	responds to user input with mouse. This method is called wheneve a mouse button is clicked
	or released. All re-implementations must explicitly call the super call version too (as per
	the SmartGL library manual).
	*/

	Activity::MouseEvents(button, state, x, y);		// Call to superclass method

	if (button == GLUT_LEFT_BUTTON && state == 0)	// When left mouse button is clicked
	{
		if (!showSidebar)								// If sidebar is hidden
		{
			if (getButton("UI_0").isClicked(x, y))			// reveal it when the sidebar
				showSidebar = true;							// button is clicked.
		}

		else if (showSidebar)							// If the sidebar is shown
		{
			showSidebar = false;							// hide the sidebar, and

			if (getButton("UI_1").isClicked(x, y))				// if first button is clicked
				App.setActive("Dictionary");					// go to dictionary activity

			else if (getButton("UI_2").isClicked(x, y))			// if second button is clicked
				App.setActive("Games");							// go to games activity

		//	else if (getButton("UI_3").isClicked(x, y))			// if third button is clicked
		//		App.setActive("Settings");						// go to settings activity

			else if (getButton("UI_4").isClicked(x, y))			// if fourth button is clicked
				App.setActive("About");							// go to about activity

			else if (getButton("UI_5").isClicked(x, y)){		// if fifth button is clicked		
				glutDestroyWindow(App.ID());					// destroy app window
				exit(0);										// and exit program
			}
		}
	}
}

void GUI::loadTextures()
{
	/*
	loadTexture() is a static method which loads the images which will be shared
	across all the activities. These images are loaded only once (only when they
	have not yet been loaded).
	*/

	if (images == NULL)
	{
		images = new Texture[7];
		images[0].loadFromFile("res/drawable/sidebar/menu.png");
		images[1].loadFromFile("res/drawable/sidebar/dictionary.png");
		images[2].loadFromFile("res/drawable/sidebar/games.png");
		images[3].loadFromFile("res/drawable/sidebar/settings.png");
		images[4].loadFromFile("res/drawable/sidebar/about.png");
		images[5].loadFromFile("res/drawable/sidebar/exit.png");
		images[6].loadFromFile("res/drawable/sidebar/overlay.png");
	}
}

void GUI::createSidebar()
{
	/*
	createSidebar() loades textures and creates buttons for the sidebar which
	will be displayed on all activities of this application.
	*/

	textures.load("Sidebar", "res/drawable/sidebar/background.png");	// Load sidebar background
	textures.get("Sidebar").setPosition(0, 0);					// and initialize its position
	textures.get("Sidebar").setSize(252, 572);					// on screen and size.

	addButton("UI_0", Button(&images[0], 40, 523, 30, 30));		// Menu button
	addButton("UI_1", Button(&images[1], 0, 350, 250, 40));		// Dictionary button
	addButton("UI_2", Button(&images[2], 0, 300, 250, 40));		// Games button
	addButton("UI_3", Button(&images[3], 0, 250, 250, 40));		// Settings button
	addButton("UI_4", Button(&images[4], 0, 200, 250, 40));		// About button
	addButton("UI_5", Button(&images[5], 0, 150, 250, 40));		// Exit button
	addButton("UI_6", Button(&images[6], 252, 0, 548, 572));	// Overlay button
}