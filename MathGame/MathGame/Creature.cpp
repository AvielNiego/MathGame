#include "Creature.h"


Creature::~Creature()
{
	removeFromScreen();
}

void Creature::kill()
{
	cleanFromScreen();
	removeFromScreen();
	delete this;
}

bool Creature::isDeadByShot() const
{
	return false;
}