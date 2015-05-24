//NEW CODE EX1, author=Aviel Niego 203839170, date=<2015-05-01>

#include "OtonomicEntities.h"

OtonomicEntities::OtonomicEntities(ScreenObject*** screen, int locationRow, int locationCol, int screenHight, int screenLength) : 
GameEntities(screen, locationRow, locationCol, screenHight, screenLength), isDead(false)
{}

void OtonomicEntities::kill()
{
	cleanFromScreen();
	removeFromScreen();
	isDead = true;
}

// END of NEW CODE EX1
