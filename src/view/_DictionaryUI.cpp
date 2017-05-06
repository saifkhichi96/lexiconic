#include "_DictionaryUI.hpp"

/*
Default public constructor for the DictionaryUI class. It loads images and creates
othere user interface elements that will be shared across all Dictionary activities.
*/
DictionaryUI::DictionaryUI()
	: insertingWord(false), updatingDefinition(false), wordBoxSelected(false),
	definitionBoxSelected(false), activeScreen(""), word(""), definition("")
{
	loadTextures();
	createButtons();
}

/*
Display() method overrides a superclass method and defines UI layout.
It may also call superclass implementation of this method if necessary.
*/
void DictionaryUI::Display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	textures.get("Dictionary").Display();

	if (activeScreen.empty())
	{
		textures.get("Summary").Display();

		gout.setFont(GLUT_BITMAP_TIMES_ROMAN_24);
		gout.setPosition(75, 325);
		gout << dailyWordScreen.GetWord();

		gout.setFont(GLUT_BITMAP_HELVETICA_10);
		gout.setPosition(160, 273);
		string update = "";
		update += to_string(23 - Date().hours) += " : ";
		update += to_string(59 - Date().minutes) += " : ";
		update += to_string(60 - Date().seconds);
		gout << update;

		// Vocabank
		auto words = vocaBankScreen.GetWords();
		gout.setColor(Black);
		gout.setFont(GLUT_BITMAP_HELVETICA_12);
		gout.setPosition(445, 360);
		for (int i = 0; i < 20; i++)
		{
			gout << string(words[i].getWord());
			gout.translate('y', -15);
		}

		gout.setFont(GLUT_BITMAP_HELVETICA_10);
		gout.setPosition(510, 43);	gout << update;

		getButton("Add").Display();
		getButton("Update").Display();

		if (insertingWord || updatingDefinition)
		{
			insertingWord ?
				textures.get("AddWord").Display() :
				textures.get("EditWord").Display();

			gout.setFont(GLUT_BITMAP_HELVETICA_18);
			gout.setPosition(165, 400);	gout << word;

			gout.setLineWidth(50);
			gout.setPosition(165, 325);	gout << definition;
		}
	}

	else if (activeScreen == "Word of the Day")
		dailyWordScreen.Display();

	else if (activeScreen == "Vocabulary Bank")
		vocaBankScreen.Display();

	searchScreen.Display();

	if (!insertingWord && !updatingDefinition) GUI::Display();
}

void DictionaryUI::KeyboardEvents(unsigned char& key, int& x, int& y)
{
	if (insertingWord || updatingDefinition)
	{
		if (word != "" && definition != "" && key == ENTER)
		{
			insertingWord ?
				userDictionary.insert(word, definition) :
				userDictionary.update(word, definition);

			userDictionary.diskOut("data/user.txt");
			word = "";
			definition = "";
			insertingWord = false;
			updatingDefinition = false;
			return;
		}

		if (wordBoxSelected)
		{
			switch (key)
			{
			case BACKSPACE:
				if (word != "")
				{
					string hold = word;
					word = "";
					for (unsigned int i = 0; i < hold.length() - 1; i++)
						word += hold[i];
				}
				break;
			default:
				word += key;
				break;
			}
		}
		else if (definitionBoxSelected)
		{
			switch (key)
			{
			case BACKSPACE:
				if (definition != "")
				{
					string hold = definition;
					definition = "";
					for (unsigned int i = 0; i < hold.length() - 1; i++)
						definition += hold[i];
				}
				break;
			default:
				definition += key;
				break;
			}
		}
	}
	else searchScreen.KeyboardEvents(key, x, y);
}

void DictionaryUI::MouseEvents(int& button, int& state, int& x, int& y)
{
	if (!showSidebar && button == 0 && state == 0)
	{
		if (insertingWord || updatingDefinition)
		{
			if (getButton("Word").isClicked(x, y))
			{
				wordBoxSelected = true;
				definitionBoxSelected = false;
			}
			else if (getButton("Definition").isClicked(x, y))
			{
				wordBoxSelected = false;
				definitionBoxSelected = true;
			}
			else
			{
				wordBoxSelected = false;
				definitionBoxSelected = false;
				insertingWord = false;
				updatingDefinition = false;
			}
			return;
		}

		if (getButton("D_1").isClicked(x, y))
			activeScreen.clear();

		else if (getButton("D_2").isClicked(x, y))
			activeScreen = "Word of the Day";

		else if (getButton("D_3").isClicked(x, y))
			activeScreen = "Vocabulary Bank";

		else if (activeScreen == "")
		{
			if (getButton("Add").isClicked(x, y))
				insertingWord = true;

			else if (getButton("Update").isClicked(x, y))
				updatingDefinition = true;
		}
		searchScreen.MouseEvents(button, state, x, y);
	}

	GUI::MouseEvents(button, state, x, y);
}

void DictionaryUI::PassiveMotionEvents(int& x, int& y)
{
	for (int i = 1; i < 4; i++)
	{
		string id = "D_" + to_string(i);

		if (getButton(id).isClicked(x, y))
		{
			activeButton = id;
			break;
		}
		else activeButton = "NULL";
	}

	searchScreen.PassiveMotionEvents(x, y);

	GUI::PassiveMotionEvents(x, y);
}

void DictionaryUI::IdleGL()
{
	dailyWordScreen.IdleGL();
	vocaBankScreen.IdleGL();
}

void DictionaryUI::onStart()
{
	if (activeScreen == "Default")
		searchScreen.onStart();
}

void DictionaryUI::onStop()
{
	if (activeScreen == "Default")
		searchScreen.onStop();
}

void DictionaryUI::loadTextures()
{
	textures.load("Dictionary", "res/drawable/dictionary/background.png");
	textures.get("Dictionary").setSize(800, 600);
	textures.get("Dictionary").setPosition(0, 0);

	textures.load("Summary", "res/drawable/dictionary/summary.png");
	textures.get("Summary").setSize(800, 600);
	textures.get("Summary").setPosition(0, 0);

	textures.load("AddWord", "res/drawable/dictionary/add_word.png");
	textures.get("AddWord").setSize(800, 600);
	textures.get("AddWord").setPosition(0, 0);

	textures.load("EditWord", "res/drawable/dictionary/update_word.png");
	textures.get("EditWord").setSize(800, 600);
	textures.get("EditWord").setPosition(0, 0);

	textures.load("Button", "res/drawable/button_highlight.png");
	textures.load("Add", "res/drawable/add.png");
	textures.load("Update", "res/drawable/edit.png");
}

void DictionaryUI::createButtons()
{
	addButton("D_1", Button(new Texture(textures.get("Button")), 75, 460, 45, 40));		// Home
	addButton("D_2", Button(new Texture(textures.get("Button")), 155, 460, 125, 40));	// Word of the Day
	addButton("D_3", Button(new Texture(textures.get("Button")), 305, 460, 95, 40));	// VocaBank

	addButton("Add", Button(new Texture(textures.get("Add")), 320, 120, 35, 35));		// Add new word
	addButton("Update", Button(new Texture(textures.get("Update")), 320, 80, 35, 35));	// Update a word

	addButton("Word", Button("", 155, 400, 490, 45));
	addButton("Definition", Button("", 155, 100, 490, 250));
}