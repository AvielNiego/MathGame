//NEW CODE EX3, author=Aviel Niego 203839170, date=<2015-05-24>
#include "Creature.h"


Creature::~Creature()
{
	removeFromScreen();
}

bool Creature::isDeadByShot() const
{
	return false;
}
// END of NEW CODE EX3