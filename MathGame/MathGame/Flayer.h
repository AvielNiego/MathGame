//NEW CODE EX3, author=Aviel Niego 203839170, date=<2015-05-24>

#ifndef _FLAYER_H_
#define _FLAYER_H_
#include "Creature.h"
class Flayer :
	public Creature
{
protected:
	Direction::value movingDir;

public:


	Flayer(ScreenObject*** screen, int locationRow, int locationCol, int screenHight, int screenLength, Direction::value moving_dir)
		: Creature(screen, locationRow, locationCol, screenHight, screenLength),
		  movingDir(moving_dir)
	{
	}

	void move();
};
#endif
// END of NEW CODE EX3