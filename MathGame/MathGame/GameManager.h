//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// GameManager.h
// -------------
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
// 30/3/2015      Aviel Niego 203839170   Change menu options
//										  ADD void showInstructions();
//											  void startGameFromSpecificLevel();
// In the file itself, add above each change/addition a remark saying: "NEW CODE EX1, author=<name>, date=<YYYY-MM-DD>"
// and close it at the end with a remark saying "END of NEW CODE EX1" 
//
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#ifndef _GAME_MANAGER_H_
#define _GAME_MANAGER_H_

#include "ISpecificGame.h"
#include <string>
#include <list>


using namespace std;

class GameManager
{
	ISpecificGame& actualGame;
	unsigned int currentLevel;
	unsigned int clockCycleInMillisec;
	unsigned int iterationsPerClockCycle;
	const static unsigned int KEYBOARD_HIT_LOOP = 10;  // const static can be initialized like this! :-)
	const static char ESC = 27; // the ESC key
public:
	GameManager(ISpecificGame& theSpecificGame, unsigned int clockCycleLengthInMillisec, unsigned int numIterationsPerClockCycle)
		:actualGame(theSpecificGame), currentLevel(0), clockCycleInMillisec(clockCycleLengthInMillisec), iterationsPerClockCycle(numIterationsPerClockCycle) {}
	void run();
private:
	// helper methods
	//NEW CODE EX1, author=Aviel Niego 203839170, date=<2015-03-23>
	void init(int startFromLevel = 1)
	{
		currentLevel = startFromLevel;
		actualGame.setLevel(startFromLevel);
	}
	// END of NEW CODE EX1
	char mainMenu()const;
	bool playGame();
	char playNextLevel();
	char doLevelIterations();
	bool doIteration();
	bool doInputIteration();
public:
	class MainMenuOptions
	{
	public:
		static bool isValidOption(char option) {
			string validOptions = "1239";
			return (validOptions.find(option) != string::npos);
		}
		enum
		{
			PRESENT_INSTRUCTIONS		=	'1',
			PLAY_GAME					=	'2',
			PLAY_FROM_SELECTED_SCREEN	=	'3',
			EXIT_APPLICATION			=	'9'
		};
	};
	class LevelOptions
	{
	public:
		static bool isValidOption(char option) {
			//NEW CODE EX1, author=Aviel Niego 203839170, date=<2015-03-23>
			string validOptions = "45678";
			// END of NEW CODE EX1
			return (validOptions.find(option) != string::npos);
		}
		enum
		{
			//NEW CODE EX1, author=Aviel Niego 203839170, date=<2015-03-23>
			EXIT_APPLICATION			=	'4',
			BACK_TO_MAIN_MENU			=	'5',
			CONTINUE					=	'6',
			REPLAY_LEVEL				=	'7',
			NEXT_LEVEL					=	'8'
			// END of NEW CODE EX1
		};
	};
	//NEW CODE EX1, author=Aviel Niego 203839170, date=<2015-03-23>
private:
	void showInstructions();
	void startGameFromSpecificLevel();
	// END of NEW CODE EX1
};

#endif