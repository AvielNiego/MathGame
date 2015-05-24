//NEW CODE EX3, author=Aviel Niego 203839170, date=<2015-05-24>

#ifndef _COL_FLAYER_H_
#define _COL_FLAYER_H_
#include "Flayer.h"
class ColFlayer :
	public Flayer
{
public:

	ColFlayer(ScreenObject*** screen, int locationRow, int locationCol, int screenHight, int screenLength, Direction::value moving_dir);


	string getScreenString() const;
	bool isEatenByPlayer() const;
	bool isEatPlayer() const;
	bool isFastCreature() const;
};
#endif
// END of NEW CODE EX3