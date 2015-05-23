//NEW CODE EX1, author=Aviel Niego 203839170, date=<2015-03-20>

#ifndef _THE_MATH_GAME_H_
#define _THE_MATH_GAME_H_

#include "ISpecificGame.h"
#include "ScreenObject.h"
#include "io_utils.h"
#include "NumberScreenObject.h"
#include <list>
#include "Player.h"
#include "OtonomicEntities.h"
#include <list>

class TheMathGame : public ISpecificGame
{
private:
	static const char BORDER_CHAR = '_';

	static const int GAME_SCREEN_START_ROW = 3;
	static const int BASE_DIFFICULTY_LEVEL = 10;
	static const int MAX_LEVEL = 40;
	static const int MAX_ITERATIONS = 1500;

	ScreenObject*** screen;

	int screenHight, screenLength;
	int screenLevel;
	int iterationCounter;
	
	list<Player*> *players;
public:
	TheMathGame(int screenHight, int screenLength) :screenHight(screenHight), screenLength(screenLength), screenLevel(0), 
		players(new list < Player* >)
	{
		initScreen();
		initGame();
	}
	~TheMathGame();

	virtual void setLevel(int startLevel)
	{
		screenLevel = startLevel;
		screenLevel--;
	}

	virtual int getMaxLevel()const
	{
		return MAX_LEVEL;
	}
	virtual void redrawScreen()const;
	virtual bool isLevelDone()const;

	virtual void initGame();

	virtual string getEndOfGameMessage()const;
	
	bool hasWinner() const;

	bool areAllPlayersDead() const;
	void createCreatures();

	virtual bool hasNextLevel()const{ return screenLevel < MAX_LEVEL; }

	virtual void startLevel();
	void deleteDeadShots();
	void pushEntity(list<OtonomicEntities*>* otonomicEntitiesToMove, OtonomicEntities*& otonomicEntity);
	void moveOtonomicObjects(bool moveFastObjectsOnly);
	virtual void doIteration(const list<char>& keyHits);
	virtual void doSubIteration();
private:
	void locateNewNumber();
	bool isAreaEmpty(int row, int col);

	int getDifficultyLevel()
	{
		return screenLevel + BASE_DIFFICULTY_LEVEL;
	}

	void killScreenObjects();
	void initPlayers();
	void initScreen();

	void drawBorder() const;
	void drawScreen() const;
	
	void drawLevel()const
	{
		gotoxy(30, 1);
		cout << "Level: " << screenLevel;
	}
};

#endif

// END of NEW CODE EX1