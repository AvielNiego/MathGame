//NEW CODE EX1, author=Aviel Niego 203839170, date=<2015-03-23>

#include "GameEntities.h"
#include "Direction.h"

void GameEntities::respawnKill()
{
	kill();
}

ScreenObject* GameEntities::getObjectAt(Direction::value direction) const
{
	switch (direction)
	{
	case Direction::UP:
		return locationRow == 0 ? screen[screenHight - 1][locationCol] : screen[locationRow - 1][locationCol];

	case Direction::DOWN:
		return locationRow == screenHight - 1 ? screen[0][locationCol] : screen[locationRow + 1][locationCol];

	case Direction::LEFT:
		return locationCol == 0 ? screen[locationRow][screenLength - 1] : screen[locationRow][locationCol - 1];

	case Direction::RIGHT:
		return locationCol == screenLength - 1 ? screen[locationRow][0] : screen[locationRow][locationCol + 1];

	default:
		return screen[locationRow][locationCol];
	}
}

int GameEntities::eatNumber(ScreenObject* screenObjectBeside)
{
	NumberScreenObject* numberBeside = dynamic_cast<NumberScreenObject*>(screenObjectBeside);
	if (numberBeside == 0)
	{
		return -1;
	}
	else
	{
		int number = numberBeside->getNumber();
		numberBeside->cleanFromScreen();
		numberBeside->removeFromScreen();
		delete numberBeside;

		return number;
	}
}

void GameEntities::moveTo(Direction::value directionToMove)
{
	cleanFromScreen();
	removeFromScreen();

	switch (directionToMove)
	{
	case Direction::UP:
		locationRow = locationRow == 0 ? screenHight - 1 : locationRow - 1;
		break;
	case Direction::DOWN:
		locationRow = locationRow == screenHight - 1 ? 0 : locationRow + 1;
		break;
	case Direction::LEFT:
		locationCol = locationCol == 0 ? screenLength - 1 : locationCol - 1;
		break;
	case Direction::RIGHT:
		locationCol = locationCol == screenLength - 1 ? 0 : locationCol + 1;
		break;
	}

	screen[locationRow][locationCol] = this;
	printToScreen();
}

// END of NEW CODE EX1