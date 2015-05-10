//NEW CODE EX1, author=Aviel Niego 203839170, date=<2015-05-01>

#ifndef _SHOT_H_
#define _SHOT_H_

#include "OtonomicEntities.h"

class Shot :
	public OtonomicEntities
{
	static const char SHOT_CHARACTER = '*';
	
	const Direction::value movingDirection;

public:
	Shot(ScreenObject*** screen, int locationRow, int locationCol, int screenHight, int screenLength, Direction::value movingDirection);
	~Shot();

	void move() override;
	string getScreenString() const override;
	bool isEatenByPlayer() const override;
	bool isEatPlayer() const override;
	bool isDeadByShot() const override;
	bool isFastCreature() const override;
	void kill() override;
};

#endif
// END of NEW CODE EX1