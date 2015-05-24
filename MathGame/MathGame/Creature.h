//NEW CODE EX3, author=Aviel Niego 203839170, date=<2015-05-24>

#ifndef _CREATURE_H_
#define _CREATURE_H_
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


	bool isDeadByShot() const;
};
#endif
// END of NEW CODE EX3