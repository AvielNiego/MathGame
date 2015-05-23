//NEW CODE EX1, author=Aviel Niego 203839170, date=<2015-05-01>

#include "Shot.h"

Shot::Shot(ScreenObject*** screen, int locationRow, int locationCol, int screenHight, int screenLength, Direction::value movingDirection): OtonomicEntities(screen, locationRow, locationCol, screenHight, screenLength), movingDirection(movingDirection)
{
	move();
	move();
}

Shot::~Shot()
{
	cleanFromScreen();
	removeFromScreen();
}

void Shot::move()
{
	ScreenObject* screenObjectBeside = getObjectAt(movingDirection);

	if (screenObjectBeside == NULL)
	{
		moveTo(movingDirection);
	}
	else
	{
		// If screenObjectBeside is not a number, the function won't do nothing
		if (eatNumber(screenObjectBeside) == -1)
		{
			GameEntities* gameEntityBeside = dynamic_cast<GameEntities*>(screenObjectBeside);

			if (gameEntityBeside != NULL && gameEntityBeside->isDeadByShot())
			{
				gameEntityBeside->respawnKill();
			}
		}
		kill();
	}
}

string Shot::getScreenString() const
{
	stringstream ss;
	string s;
	ss << SHOT_CHARACTER;
	ss >> s;
	return s;
}

bool Shot::isEatenByPlayer() const
{
	return true;
}

bool Shot::isEatPlayer() const
{
	return true;
}

bool Shot::isDeadByShot() const
{
	return true;
}

bool Shot::isFastCreature() const
{
	return true;
}

void Shot::kill()
{
	cleanFromScreen();
	removeFromScreen();
	isDead = true;
}

// END of NEW CODE EX1