#include <Windows.h>
#include <chrono>
#include <thread>
#include <ctime>
#include "util/Map.hpp"
#include "view/GUI.hpp"

#pragma comment (lib, "../libs/SmartGL.lib")


Dictionary	wordList;
Dictionary	userDictionary;


void loadDictionary(int lower, int upper)
{
	/*
	loadDictionary() method loads data from files into it the dictionary object
	Address of this object is passed to the global pointer wordList. This function will
	be executed in its own thread so that loading process does not interrupt the user
	experience or the flow of program.
	*/

	/*
	Read data from files into memory
	Data is stored in 26 different files and is loaded from each one by one
	Including time functions to monitor how long loading takes.
	*/
	auto start = chrono::high_resolution_clock::now();
	for (int index = lower; index <= upper; index++)
	{
		wordList.diskIn("res/values/" + to_string(index) + "_List.txt");
	}
	cout << "Success (" << char('A' + lower - 1) << "-" << char('A' + upper - 1) << " "
		<< chrono::duration_cast<chrono::seconds>(chrono::high_resolution_clock::now() - start).count()
		<< " seconds)" << endl;
}


void StartGLUT()
{
	/*
	Create an OpenGL window and set the first activity as SPLASH
	*/
	App.Initialize(800, 600, "DICTIONARY");

	/*
	Activities (screens) in the game. Each activity has its own display method, and event handlers.
	Base class pointer will be used to access each activity polymorphically
	*/
	App.addActivity(new Splash(), "Splash");
	App.setActive("Splash");

	/*
	Start app
	*/
	App.run();
}

// Uncomment the following line to start App
//#define APP_RUN
#ifdef APP_RUN
int main()
{
	FreeConsole();
	srand(time(NULL));

	try {
		/*
		Start the process of loading data from files
		Data is loaded asynchronously, i.e. program continues its execution
		and does not wait for loading to be completed. Detach all threads so
		that they may continue executing even if they were to go out of scope.
		*/
		cout << "Loading dictionary ... \n";
		thread(loadDictionary, 1, 6).detach();
		thread(loadDictionary, 7, 16).detach();
		thread(loadDictionary, 17, 26).detach();
		userDictionary.diskIn("res/values/user.txt");

		/*
		Create a GLUT window, register callbacks, initialize states
		and start the program
		*/
		StartGLUT();
	}
	catch (exception &ex){
		cout << ex.what() << " ... TERMINATING NOW" << endl;
		return EXIT_FAILURE;
	}
	catch (...){
		cout << "UNKNOWN EXCEPTION THROWN ... TERMINANTING NOW" << endl;
		return EXIT_FAILURE;
	}
	system("pause");
	return EXIT_SUCCESS;
}
#endif