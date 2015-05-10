//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// GameManager.cpp
// ---------------
// GameManager is the top level manager, the game starts from here.
// This class manages the game iterations, menus etc., but WITHOUT knowing anything about the actual game itself.
//
// Author: Amir Kirsh
// First version: 2014-12-09
// 
// This code is part of "the math game" excercise in C++ course, Semester B 2015
// at the Academic College of Tel-Aviv-Yaffo.
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// Changes and additions:
// ------------------------
// DATE           Authors                 Change / Addition
// ----           --------                -----------------
// In the file itself, add above each change/addition a remark saying: "NEW CODE EX1, author=<name>, date=<YYYY-MM-DD>"
// and close it at the end with a remark saying "END of NEW CODE EX1" 
//
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#include <list>
#include "GameManager.h"
#include "ISpecificGame.h"
#include "io_utils.h"

using namespace std;

char GameManager::mainMenu()const
{
	cout << "1. instructions" << endl;
	cout << "2. play game" << endl;
	cout << "3. start from a specific level" << endl;
	cout << "9. exit" << endl;
	char selection = 0;
	do {
		selection = _getch();
	} while(!GameManager::MainMenuOptions::isValidOption(selection));
	return selection;
}

//NEW CODE EX1, author=Aviel Niego 203839170, date=<2015-03-23>

void GameManager::showInstructions()
{
	clear_screen();
	cout << "Use keyboard to move and get the number you need to solve the exersice!" << endl;
	cout << "keys for @: w,a,x,d" << endl;
	cout << "keys for #: i,j,m,l" << endl;
	cout << "press any key to continue";
	_getch();
	clear_screen();
}

void GameManager::startGameFromSpecificLevel()
{
	clear_screen();
	cout << "Enter screen number you want to start with, then press ENTER:" << endl;

	char c = _getch();
	string strScreenNumberInput = "";
	while (c != 13)
	{
		if (c >= '0' && c <= '9')
		{
			cout << c;
			strScreenNumberInput = strScreenNumberInput + c;
		}
		c = _getch();
	}
	int screenToStartWith = atoi(strScreenNumberInput.c_str());
	
	if (screenToStartWith > actualGame.getMaxLevel())
	{
		screenToStartWith = actualGame.getMaxLevel();
	}
	if (screenToStartWith == 0)
	{
		screenToStartWith = 1;
	}

	clear_screen();
	init(screenToStartWith);
}

// END of NEW CODE EX1

void GameManager::run()
{
	bool userWantsToPlay = true;
	// we run as long as the user wants
	while(userWantsToPlay) {
		char menuSelection = mainMenu();
		// TODO: handle here all the different menu options
		switch(menuSelection)
		{
		case GameManager::MainMenuOptions::PLAY_GAME:
			init();
			userWantsToPlay = playGame();
			break;
			//NEW CODE EX1, author=Aviel Niego 203839170, date=<2015-03-30>
		case GameManager::MainMenuOptions::PLAY_FROM_SELECTED_SCREEN:
			startGameFromSpecificLevel();
			userWantsToPlay = playGame();
			break;
		case GameManager::MainMenuOptions::PRESENT_INSTRUCTIONS:
			showInstructions();
			break;
			// END of NEW CODE EX1
		case GameManager::MainMenuOptions::EXIT_APPLICATION:
			userWantsToPlay = false;
			break;
		default: // normally we shouldn't get to here...
			userWantsToPlay = false;
		};
	}
}

bool GameManager::playGame()
{
	// we assume that we have multiple levels so there is a need to loop through levels
	// till all levels were played or till user quits - if user quits we do not continue to next level
	//-------------------------------------------------------------
	// this is the game LEVELS loop
	//-------------------------------------------------------------
	char action = GameManager::LevelOptions::NEXT_LEVEL;
	while(actualGame.hasNextLevel() && action == GameManager::LevelOptions::NEXT_LEVEL) {
		action = playNextLevel();
	}
	//-------------------------------------------------------------
	// END of game LEVELS loop
	//-------------------------------------------------------------
	
	// return true if the user wants to keep playing
	return (action != GameManager::LevelOptions::EXIT_APPLICATION);
}

// return action to take in case of ESC
char GameManager::playNextLevel()
{
	++currentLevel;
	actualGame.startLevel();
	
	//------------------------------------------------------------------------------
	// here we control the ESC menu
	//------------------------------------------------------------------------------
	bool keepRunning = true;
	char action = 0;
	while(keepRunning)
	{
		//=============================================================================================
		// this is the actual call to play game iterations
		action = doLevelIterations();
		//=============================================================================================
		
		// check action based on game ended (action==BACK_TO_MAIN_MENU) or input from user on ESC menu
		switch(action) {
		case GameManager::LevelOptions::CONTINUE:
			actualGame.redrawScreen();
			break;
		case GameManager::LevelOptions::REPLAY_LEVEL:
			actualGame.setLevel(currentLevel);
			actualGame.startLevel();
			break;
		case GameManager::LevelOptions::BACK_TO_MAIN_MENU:
			//NEW CODE EX1, author=Aviel Niego 203839170, date=<2015-03-23>
			actualGame.initGame();
			// END OF NEW CODE
		case GameManager::LevelOptions::EXIT_APPLICATION:
			// get out from the loop
			clear_screen();
			keepRunning = false;
			break;
		case GameManager::LevelOptions::NEXT_LEVEL:
			// get out from the loop so we get to the next level
			keepRunning = false;
			break;
		}
		//---------------------------------------
		// END of sub menu action switch
		//---------------------------------------
	}
	//------------------------------------------
	// END of Level keepRunning loop (sub menu)
	//------------------------------------------

	// the actions that may get out from this method are: BACK_TO_MAIN_MENU and EXIT_APPLICATION
	return action;
}

// return action to take in case of ESC
char GameManager::doLevelIterations()
{
	char action;
	bool escapePressed = false;
	//---------------------------------------
	// this is the game iterations loop
	//---------------------------------------
	while(!actualGame.isLevelDone() && !escapePressed) {
		escapePressed = !doIteration();
	}
	//-----------------------------------------------------
	// END of game iterations loop or exit on ESC
	//-----------------------------------------------------

	// check why we are here
	if(actualGame.isLevelDone()) {
		clear_screen();
		//NEW CODE EX1, author=Aviel Niego 203839170, date=<2015-03-23>
		cout << endl << actualGame.getEndOfGameMessage() << endl;
		cout << "press ENTER to continue";
		while(_getch() != 13);
		// END of NEW CODE EX1
		action = GameManager::LevelOptions::NEXT_LEVEL;
	}
	else if(escapePressed) {
		action = 0;
		//NEW CODE EX1, author=Aviel Niego 203839170, date=<2015-03-23>
		clear_screen();
		cout << "4. exit game" << endl;
		cout << "5. back to main menu" << endl;
		cout << "6. continue" << endl;
		cout << "7. replay level" << endl;
		cout << "8. next level" << endl;
		// END of NEW CODE EX1
		do {
			action = _getch();
		} while(!GameManager::LevelOptions::isValidOption(action));
	}
	// end of esc pressed
	clear_screen();
	return action;
}

bool GameManager::doIteration()
{
	unsigned int sleepLength = clockCycleInMillisec/iterationsPerClockCycle;
	for(unsigned int i=0; i<iterationsPerClockCycle-1; ++i) {
		Sleep(sleepLength);
		actualGame.doSubIteration();
	}
	return doInputIteration();
}

bool GameManager::doInputIteration()
{
	list<char> keyHits(KEYBOARD_HIT_LOOP); // set vector initialize size to the max key strokes that we may collect
	bool shouldContinue = true;
	// get keyboard input in a loop, to get enough keyboard hits
	unsigned int sleepLength = clockCycleInMillisec/iterationsPerClockCycle / KEYBOARD_HIT_LOOP;
	for(unsigned int i=0; i<KEYBOARD_HIT_LOOP; ++i) {
		Sleep(sleepLength);
		if (_kbhit()) {
			char ch = _getch();
			if(ch == ESC) {
				// ESC pressed
				shouldContinue = false;
			}
			else {
				// we got keyHits byref, so we actually set input into the original list sent here
				keyHits.push_front(ch); // we want recent keys to come first, thus we use push_front
			}
		}
	}
	// send the keystrokes to the game
	// (even if ESC was hit, we may still have something in the keystrokes vector and should use it)
	actualGame.doIteration(keyHits);

	return shouldContinue;
}

