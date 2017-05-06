#include "GUI.hpp"

About::About()
{
	textures.load("About", "res/drawable/About.png");
	textures.get("About").setSize(800, 600);
	textures.get("About").setPosition(0, 0);

	textures.load("Back", "res/drawable/back_arrow_white.png");

	addButton("Back", Button(new Texture(textures.get("Back")), 730, 523, 30, 30));
}

void About::Display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	textures.get("About").Display();

	getButton("Back").Display();
	GUI::Display();
}

void About::MouseEvents(int& button, int& state, int& x, int& y)
{
	if (button == 0 && state == 0)
	{
		(!showSidebar && getButton("Back").isClicked(x, y)) ?
			App.setActive("Dictionary") :
			GUI::MouseEvents(button, state, x, y);
	}
}
