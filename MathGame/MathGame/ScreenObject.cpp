//NEW CODE EX1, author=Aviel Niego 203839170, date=<2015-03-23>

#include "ScreenObject.h"

void ScreenObject::removeFromScreen()
{
	screen[locationRow][locationCol] = NULL;
}

void ScreenObject::cleanFromScreen() const
{
	if (screen[locationRow][locationCol] == NULL ||  screen[locationRow][locationCol]->getScreenString() == getScreenString())
	{
		gotoxy(locationCol, locationRow + SCREEN_START_ROW);
		cout << ' ';
	}
}

void ScreenObject::printToScreen() const
{
	gotoxy(locationCol, locationRow + SCREEN_START_ROW);
	cout << getScreenString();
}

// END of NEW CODE EX1