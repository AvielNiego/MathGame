//NEW CODE EX1, author=Aviel Niego 203839170, date=<2015-03-20>

#ifndef _GAME_ENTITIES_H_
#define _GAME_ENTITIES_H_

#include "ScreenObject.h"
#include <string>
#include "Direction.h"
#include "NumberScreenObject.h"

using namespace std;

class GameEntities : public ScreenObject
{

public:
	GameEntities(ScreenObject ***screen, int locationRow, int locationCol, int screenHight, int screenLength) :
		ScreenObject(screen, locationRow, locationCol, screenHight, screenLength){}

	virtual string getScreenString()const = 0;
	virtual bool isEatenByPlayer()const = 0;
	virtual bool isEatPlayer()const = 0;
	virtual bool isDeadByShot()const = 0;
	virtual bool isFastCreature()const = 0;
	virtual void kill() = 0;
	void respawnKill();

protected:
	ScreenObject* getObjectAt(Direction::value direction);
	int eatNumber(ScreenObject* screenObjectBeside);
	void moveTo(Direction::value directionToMove);
};

#endif

// END of NEW CODE EX1