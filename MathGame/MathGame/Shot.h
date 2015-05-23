//NEW CODE EX1, author=Aviel Niego 203839170, date=<2015-05-01>

#ifndef _SHOT_H_
#define _SHOT_H_

#include "OtonomicEntities.h"

class Shot :
	public OtonomicEntities
{
	static const char SHOT_CHARACTER = '*';
	
	Direction::value movingDirection;

public:
	Shot(ScreenObject*** screen, int locationRow, int locationCol, int screenHight, int screenLength, Direction::value movingDirection);
	~Shot();

	Direction::value getMovingDirection() const
	{
		return movingDirection;
	}

	void move();
	string getScreenString() const;
	bool isEatenByPlayer() const;
	bool isEatPlayer() const;
	bool isDeadByShot() const;
	bool isFastCreature() const;
	void kill();
};

#endif
// END of NEW CODE EX1