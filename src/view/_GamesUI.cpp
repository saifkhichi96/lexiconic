#include "_GamesUI.hpp"


GamesUI::GamesUI()
{
	textures.load("Games", "res/drawable/Games.tga");
	textures.get("Games").setPosition(0, 0);
	textures.get("Games").setSize(800, 600);

	textures.load("Button", "res/drawable/button_highlight.png");

	addButton("G_1", Button(new Texture(textures.get("Button")),  75, 460, 55, 40));
	addButton("G_2", Button(new Texture(textures.get("Button")), 170, 460, 75, 40));
	addButton("G_3", Button(new Texture(textures.get("Button")), 280, 460, 55, 40));
	addButton("G_4", Button(new Texture(textures.get("Button")), 375, 460, 85, 40));
}


void GamesUI::Display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	textures.get("Games").Display();
	GUI::Display();
}


void GamesUI::onClick(UIElement& view)
{
	if (view.getID() == "G_1")
	{
		App.setActive("Games");
	}
	else if (view.getID() == "G_2")
	{
		try{
			App.setActive("Hangman");
		}
		catch (logic_error& ex)
		{
			cout << ex.what();
			cout << "Creating activity 'Hangman'\n";
			App.addActivity(new Hangman(), "Hangman");
			App.setActive("Hangman");
		}
	}
	else if (view.getID() == "G_3")
	{
		try{
			App.setActive("Jumble");
		}
		catch (logic_error& ex)
		{
			cout << ex.what();
			cout << "Creating activity 'Jumble'\n";
			App.addActivity(new JumbleUI(), "Jumble");
			App.setActive("Jumble");
		}
	}
	else if (view.getID() == "G_4")
	{
		try{
			App.setActive("WordTrain");
		}
		catch (logic_error& ex)
		{
			cout << ex.what();
			cout << "Creating activity 'WordTrain'\n";
			App.addActivity(new WordTrainUI(), "WordTrain");
			App.setActive("WordTrain");
		}
	}
}


void GamesUI::PassiveMotionEvents(int& x, int& y)
{
	for (int i = 1; i < 5; i++)
	{
		string id = "G_" + to_string(i);

		if (getButton(id).isClicked(x, y))
		{
			activeButton = id;
			break;
		}
		else activeButton = "NULL";
	}

	GUI::PassiveMotionEvents(x, y);
}