#include "GUI.hpp"
#include "_DictionaryUI.hpp"
#include "_GamesUI.hpp"


Splash::Splash()
	: progress(0.f)
{
	// Load textures	
	textures.load("Splash", "res/drawable/Splash.png");
	textures.get("Splash").setSize(800, 600);
	textures.get("Splash").setPosition(0, 0);

	textures.load("Loading", "res/drawable/Progress Bar.png");
	textures.get("Loading").setPosition(57, 92);
}


void Splash::Display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	textures.get("Splash").Display();
	textures.get("Loading").setSize(6.9 * progress, 15);
	textures.get("Loading").Display();

	gout.setAlpha(0.5f);
	gout.setPosition(390, 75);
	gout << string(string(to_string((int)progress) + "%"));
	progress += 0.01;

	if (progress >= 100)
	{
		// Remove this activity (won't be used again)
		App.removeActivity("Slpash");

		// Add new activities
		App.addActivity(new DictionaryUI(), "Dictionary");
		App.addActivity(new SudokuUI(), "Games");
		App.addActivity(new About(), "About");
	//	App.addActivity(new About(), "Settings");

		// Set dictionary as active activity
		App.setActive("Dictionary");
	}

	glutPostRedisplay();
}