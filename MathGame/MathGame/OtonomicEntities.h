//NEW CODE EX1, author=Aviel Niego 203839170, date=<2015-05-01>

#ifndef _OTONOMIC_ENTITIES_H_
#define _OTONOMIC_ENTITIES_H_

#include "GameEntities.h"
class OtonomicEntities :
	public GameEntities
{
protected:
	bool isDead;
public:
	OtonomicEntities(ScreenObject*** screen, int locationRow, int locationCol, int screenHight, int screenLength);

	virtual void move() =0;
	bool is_dead(){ return isDead; }

	void kill();
};

#endif
// END of NEW CODE EX1
