#include "Creature.h"


Creature::~Creature()
{
	removeFromScreen();
}

void Creature::kill()
{
	removeFromScreen();
	delete this;
}

bool Creature::isDeadByShot() const
{
	return false;
}