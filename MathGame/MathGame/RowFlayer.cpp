//NEW CODE EX3, author=Aviel Niego 203839170, date=<2015-05-24>

#include "RowFlayer.h"
#include "Player.h"
#include "Shot.h"

RowFlayer::RowFlayer(ScreenObject*** screen, int locationRow, int locationCol, int screenHight, int screenLength, Direction::value moving_dir): Flayer(screen, locationRow, locationCol, screenHight, screenLength, moving_dir)
{
	if (moving_dir != Direction::RIGHT && moving_dir != Direction::LEFT)
	{
		movingDir = Direction::LEFT;
	}

	movingDir = moving_dir;

	// We print to screen here and not in Creature because the printToScreen() 
	// method is using the getScreenString() method which can only be used after the instance is created
	printToScreen();
}

string RowFlayer::getScreenString() const
{
	return "!";
}

bool RowFlayer::isEatenByPlayer() const
{
	return false;
}

bool RowFlayer::isEatPlayer() const
{
	return true;
}

bool RowFlayer::isFastCreature() const
{
	return true;
}

// END of NEW CODE EX3