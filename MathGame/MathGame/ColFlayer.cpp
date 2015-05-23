#include "ColFlayer.h"


ColFlayer::ColFlayer(ScreenObject*** screen, int locationRow, int locationCol, int screenHight, int screenLength, Direction::value moving_dir): Flayer(screen, locationRow, locationCol, screenHight, screenLength, moving_dir)
{
	if (moving_dir != Direction::UP && moving_dir != Direction::DOWN)
	{
		movingDir = Direction::UP;
	}

	movingDir = moving_dir;

	// We print to screen here and not in Creature because the printToScreen() 
	// method is using the getScreenString() method which can only be used after the instance is created
	printToScreen();
}

string ColFlayer::getScreenString() const
{
	return "$";
}

bool ColFlayer::isEatenByPlayer() const
{
	return false;
}

bool ColFlayer::isEatPlayer() const
{
	return true;
}

bool ColFlayer::isFastCreature() const
{
	return false;
}