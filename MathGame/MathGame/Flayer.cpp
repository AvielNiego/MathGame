#include "Flayer.h"
#include "Player.h"
#include "Shot.h"

void Flayer::move()
{
	ScreenObject* screenObjectBeside = getObjectAt(movingDir);

	if (screenObjectBeside == NULL)
	{
		moveTo(movingDir);
	}
	else
	{
		// If screenObjectBeside is not a number, the function won't do nothing
		if (eatNumber(screenObjectBeside) == -1)
		{
			Player* playerBeside = dynamic_cast<Player*>(screenObjectBeside);
			if (playerBeside != NULL)
			{
				playerBeside->respawnKill();
			}
			else
			{
				Shot* shotBeside = dynamic_cast<Shot*>(screenObjectBeside);
				if (shotBeside != NULL)
				{
					shotBeside->kill();
				}
				else
				{
					Creature* creatureBeside = dynamic_cast<Creature*>(screenObjectBeside);
					if (creatureBeside != NULL)
					{
						Direction::value opposite_direction = Direction::getOppositeDirection(movingDir);
						ScreenObject* screenObjectBehing = getObjectAt(opposite_direction);
						Creature* creatureBehind = dynamic_cast<Creature*>(screenObjectBehing);
						if (creatureBehind == NULL)
						{
							movingDir = opposite_direction;
							move();
						}
					}
				}
			}
		}
	}
}