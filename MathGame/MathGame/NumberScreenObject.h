//NEW CODE EX1, author=Aviel Niego 203839170, date=<2015-03-20>

#ifndef _NUMBER_SCREEN_OBJECT_H_
#define _NUMBER_SCREEN_OBJECT_H_

#include "ScreenObject.h"
#include "StringUtils.h"
#include <string>

using namespace std;

class NumberScreenObject : public ScreenObject
{
private:
	int number;

public:
	NumberScreenObject(ScreenObject*** screen, int locationRow, int locationCol, int screenHight, int screenLength, int number);
	~NumberScreenObject();

	virtual string getScreenString() const;
	int getNumber();
	void cleanFromScreen()const;
	void removeFromScreen();
};

#endif

// END of NEW CODE EX1