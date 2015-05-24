//NEW CODE EX3, author=Aviel Niego 203839170, date=<2015-05-24>

#include "Flayer.h"
#include "Player.h"
#include "Shot.h"
#include "NumberEater.h"

void Flayer::move()
{
	ScreenObject* screenObjectBeside = getObjectAt(movingDir);

	if (screenObjectBeside == NULL)
	{
		moveTo(movingDir);
	}
	else
	{
		if (eatNumber(screenObjectBeside) == -1)
		{
			Player* playerBeside = dynamic_cast<Player*>(screenObjectBeside);
			if (playerBeside != NULL)
			{
				playerBeside->respawnKill();
				moveTo(movingDir);
			}
			else
			{
				Shot* shotBeside = dynamic_cast<Shot*>(screenObjectBeside);
				if (shotBeside != NULL)
				{
					shotBeside->kill();
					moveTo(movingDir);
				}
				else
				{
					NumberEater* number_eater = dynamic_cast<NumberEater*>(screenObjectBeside);
					if (number_eater != NULL)
					{
						number_eater->kill();
						moveTo(movingDir);
						return;
					}

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
		else
		{
			moveTo(movingDir);
		}
	}
}
	// END of NEW CODE EX3