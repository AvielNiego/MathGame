//NEW CODE EX1, author=Aviel Niego 203839170, date=<2015-03-20>

#ifndef _SCREEN_OBJECT_H_
#define _SCREEN_OBJECT_H_

#include <string>
#include "io_utils.h"

using namespace std;

// An object that can be drawn to the screen
class ScreenObject
{
protected:
	static const int SCREEN_START_ROW = 3;

	ScreenObject ***screen;
	int locationRow, locationCol;
	int screenHight, screenLength;
public:
	virtual ~ScreenObject()
	{
	}

	ScreenObject(ScreenObject ***screen, int locationRow, int locationCol, int screenHight, int screenLength) :
		screen(screen), locationRow(locationRow), locationCol(locationCol), screenHight(screenHight), screenLength(screenLength)
	{
	}
	virtual string getScreenString()const=0;


	int getLocationRow() const
	{
		return locationRow;
	}

	int getLocationCol() const
	{
		return locationCol;
	}

	virtual void removeFromScreen();
	virtual void cleanFromScreen()const;
	void printToScreen()const;
};

#endif

// END of NEW CODE EX1