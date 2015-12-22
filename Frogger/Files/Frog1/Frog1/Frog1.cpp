// Frog1.cpp : Defines the entry point for the console application.


// The one header file to rule them all. Mwahahahahaha
#include "stdafx.h"
//#include <Windows.h>

// This is called if the game didn't close, and some error caused the entire program to close.
void closeApp()
{
	cout << "Press enter to continue..." << endl;
	getchar();
	exit(0);
}





// Checks the arguments to make sure that the program can execute properly.
void checkArgs(int argc, char* argv[])
{
	if (argc != 2)
	{
		cout << "Arguments error. Only specify one argument." << endl;
		closeApp();
	}
}






// The main.
void main(int argc, char* argv[])
{
	checkArgs(argc, argv);
	string u = argv[0];
	string folderpath = argv[1];
	//folderpath = "C:\Users\mousethejeff.DDEATHSTARR\Desktop\Frogger\Files\resources";
	//FreeConsole();
	Game* frogger = new Game(folderpath);

	if (frogger->Initalize() == false)
	{
		cout << "ERROR - SDL & associated libraries could not be loaded." << endl;
		closeApp();
	}
	if (frogger->LoadAssets() == false)
	{
		cout << "ERROR - A resource could not be found. Game cannot run!" << endl;
		closeApp();
	}
	frogger->GameLoop();
	frogger->Close();
}


