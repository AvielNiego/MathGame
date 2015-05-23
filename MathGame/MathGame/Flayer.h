#pragma once
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

