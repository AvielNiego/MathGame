

#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "GameEntities.h"
#include "ScreenObject.h"
#include "Direction.h"
#include "Exercise.h"
#include "NumberScreenObject.h"
#include <list>
#include <sstream>

using namespace std;

class Player : public GameEntities
{
	static const int START_LIFE = 3;
	static const int START_STACK = 5;
	static const char LIFE_CHAR = 'X';
	char playerSighn;
	char dirUp, dirLeft, dirDown, dirRight, shotKey;
	int  lifeRow, lifeCol;
	int  startLocationRow, startLocationCol;
	bool isEquationStraightenedWithLife;
	int  levelsWonCount;

	Direction::value movingDir;
	bool isWon;
	bool isAlive;
	int stack;

	Exercise *exercise;
	int life;
	Player(Player& other);
	Player& operator=(Player& other);

public:
	Player(char playerSighn, char dirUp, char dirLeft, char dirDown, char dirRight, char shotKey,
	       ScreenObject*** screen, int screenHight, int screenLength, int startLocationRow, int startLocationCol, int lifeRow, int lifeCol, bool isEquationStraightenedWithLife);

	~Player()
	{
		delete exercise;
	}

	void initPlayerForNewLevel(int maximumNumber);

	virtual string getScreenString() const;

	bool getIsAlive()const
	{
		return isAlive;
	}

	void addBullet();
	void shot();
	void moveToStartPoint();
	void respawnKill();
	void inputKey(char keyPressed);

	void move();

	int getPoints()const
	{
		return levelsWonCount;
	}

	bool getIsWon()const
	{
		return isWon;
	}

	virtual bool isEatenByPlayer() const { return false; }
	virtual bool isEatPlayer() const { return false; }
	virtual bool isDeadByShot() const { return true; }
	virtual bool isFastCreature() const { return false; }
	virtual void kill();

	void printExtra()const;
private:
	Direction::value getKeyDirection(char keyPressed);
	void printLife()const;
	void printExercise()const;
};

#endif