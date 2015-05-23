#pragma once
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

