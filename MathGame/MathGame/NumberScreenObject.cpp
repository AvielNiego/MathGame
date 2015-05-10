//NEW CODE EX1, author=Aviel Niego 203839170, date=<2015-05-09>
#include "NumberScreenObject.h"

NumberScreenObject::NumberScreenObject(ScreenObject*** screen, int locationRow, int locationCol, int screenHight, int screenLength, int number):
	ScreenObject(screen, locationRow, locationCol, screenHight, screenLength), number(number)
{
	screen[locationRow][locationCol] = this;

	if (number > 9)
	{
		screen[locationRow][locationCol + 1] = this;
	}
}

NumberScreenObject::~NumberScreenObject()
{
	removeFromScreen();
}

string NumberScreenObject::getScreenString() const
{
	return StringUtils::toString(number);
}

int NumberScreenObject::getNumber()
{
	return number;
}

void NumberScreenObject::cleanFromScreen() const
{
	gotoxy(locationCol, locationRow + SCREEN_START_ROW);

	if (number > 9)
	{
		string twoEmptySpots = "  ";
		cout << twoEmptySpots;
	}
	else
	{
		cout << ' ';
	}
}

void NumberScreenObject::removeFromScreen()
{
	screen[locationRow][locationCol] = NULL;

	if (number > 9)
	{
		screen[locationRow][locationCol + 1] = NULL;
	}
}
// END of NEW CODE EX1