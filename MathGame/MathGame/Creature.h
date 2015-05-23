#pragma once
#include "OtonomicEntities.h"
class Creature :
	public OtonomicEntities
{
public:


	Creature(ScreenObject*** screen, int locationRow, int locationCol, int screenHight, int screenLength)
		: OtonomicEntities(screen, locationRow, locationCol, screenHight, screenLength)
	{
		screen[locationRow][locationCol] = this;
	}

	~Creature();


	void kill();
	bool isDeadByShot() const;
};

