//NEW CODE EX1, author=Aviel Niego 203839170, date=<2015-03-20>

#include "ISpecificGame.h"
#include "ScreenObject.h"
#include "io_utils.h"
#include "NumberScreenObject.h"
#include "TheMathGame.h"
#include "OtonomicEntities.h"
#include "ColFlayer.h"
#include "RowFlayer.h"
#include "NumberEater.h"
#include "Shot.h"


TheMathGame::~TheMathGame()
{
	killScreenObjects();

	for (list<Player*>::iterator it = players->begin(); it != players->end(); ++it)
	{
		delete *it;
	}

	// Delete screen
	for (int i = 0; i < screenHight; ++i)
	{
		delete[] screen[i];
	}
	delete[] screen;
}

void TheMathGame::redrawScreen()const
{
	drawBorder();
	drawScreen();
	drawLevel();

	for (list<Player*>::iterator it = players->begin(); it != players->end(); ++it)
	{
		Player *player = *it;
		player->printExtra();
	}
}

bool TheMathGame::isLevelDone() const
{ 
	if (hasWinner() || areAllPlayersDead() || iterationCounter > MAX_ITERATIONS)
	{
		return true;
	}
	return false;
}

bool TheMathGame::hasWinner() const
{
	for (list<Player*>::iterator it = players->begin(); it != players->end(); ++it)
	{
		Player *player = *it;
		if (player->getIsWon())
		{
			return true;
		}
	}
	return false;
}

bool TheMathGame::areAllPlayersDead() const
{
	for (list<Player*>::iterator it = players->begin(); it != players->end(); ++it)
	{
		Player *player = *it;
		if (player->getIsAlive())
		{
			return false;
		}
	}
	return true;
}

void TheMathGame::createCreatures()
{
	new NumberEater(screen, 19, 10, screenHight, screenLength);
	new NumberEater(screen, 19, 70, screenHight, screenLength);
	new RowFlayer(screen, 20, 30, screenHight, screenLength, Direction::RIGHT);
	new RowFlayer(screen, 15, 50, screenHight, screenLength, Direction::LEFT);
	new ColFlayer(screen, 20, 45, screenHight, screenLength, Direction::UP);
	new ColFlayer(screen, 15, 55, screenHight, screenLength, Direction::UP);
}

void TheMathGame::initGame()
{
	players->clear();
	players->push_back(new Player('@', 'w', 'a', 'x', 'd', 'z', screen, screenHight, screenLength, 9, 10, 0, 0, true));
	players->push_back(new Player('#', 'i', 'j', 'm', 'l', 'n', screen, screenHight, screenLength, 9, 70, 0, screenLength - 6, false));
	killScreenObjects();
}

string TheMathGame::getEndOfGameMessage()const
{
	if (hasWinner())
	{
		string message = "Well Done! \nThe following players recived 1 point:";
		for (list<Player*>::iterator it = players->begin(); it != players->end(); ++it)
		{
			Player *player = *it;
			if (player->getIsWon())
			{
				message = message + player->getScreenString() + " ";
			}
		}
		return message;
	}
	else if (areAllPlayersDead())
	{
		return "You Should Get Better...";
	}
	else if (iterationCounter < MAX_ITERATIONS)
	{
		return "You did not finished the game, you both lost";
	}
	return "";
}

void TheMathGame::startLevel()
{
	clear_screen();
	killScreenObjects();

	screenLevel++;
	drawLevel();

	drawBorder();
	initPlayers();
	createCreatures();
	iterationCounter = 0;
}

void TheMathGame::pushEntity(list<OtonomicEntities*>* otonomicEntitiesToMove, OtonomicEntities*& otonomicEntity)
{
	Shot* shot = dynamic_cast<Shot*>(otonomicEntity);
	if (shot != NULL)
	{
		Shot* shotBeside = dynamic_cast<Shot*>(shot->getObjectAt(shot->getMovingDirection()));
		if (shotBeside != NULL && shotBeside->getMovingDirection() == shot->getMovingDirection())
		{
			otonomicEntitiesToMove->push_back(otonomicEntity);
			return;
		}
	}
	otonomicEntitiesToMove->push_front(otonomicEntity);
}

void TheMathGame::moveOtonomicObjects(bool moveFastObjectsOnly)
{
	list<OtonomicEntities*> *otonomicEntitiesToMove = new list<OtonomicEntities*>;

	for (int i = 0; i < screenHight; i++)
	{
		for (int j = 0; j <  screenLength; j++)
		{
			OtonomicEntities* otonomicEntity = dynamic_cast<OtonomicEntities*>(screen[i][j]);

			if (otonomicEntity != NULL)
			{
				if (otonomicEntity->is_dead())
				{
					delete otonomicEntity;
				}
				else
				{
					if (moveFastObjectsOnly)
					{
						if (otonomicEntity->isFastCreature())
						{
							pushEntity(otonomicEntitiesToMove, otonomicEntity);
						}
					}
					else
					{
						pushEntity(otonomicEntitiesToMove, otonomicEntity);
					}
				}
			}
		}
	}

	// Making sure we are moving every entity only one time.
	for (list<OtonomicEntities*>::iterator it = otonomicEntitiesToMove->begin(); it != otonomicEntitiesToMove->end(); ++it)
	{
		OtonomicEntities *otonomicEntity = *it;
		if (!otonomicEntity->is_dead())
		{
			otonomicEntity->move();
		}
	}

	for (list<OtonomicEntities*>::iterator it = otonomicEntitiesToMove->begin(); it != otonomicEntitiesToMove->end(); ++it)
	{
		OtonomicEntities *otonomicEntity = *it;
		if (otonomicEntity->is_dead())
		{
			delete otonomicEntity;
		}
	}

	delete otonomicEntitiesToMove;
}

void TheMathGame::killScreenObjects()
{
	for (int i = 0; i < screenHight; i++)
	{
		for (int j = 0; j < screenLength; j++)
		{
			ScreenObject* screen_object = screen[i][j];
			if (screen_object != NULL)
			{
				Player* player = dynamic_cast<Player*>(screen_object);
				if (player == NULL)
				{
					delete screen_object;
				}
			}
		}
	}
}

void TheMathGame::initPlayers()
{
	for (list<Player*>::iterator it = players->begin(); it != players->end(); ++it)
	{
		Player *player = *it;
		player->initPlayerForNewLevel(getDifficultyLevel());
	}
}

void TheMathGame::doIteration(const list<char>& keyHits)
{
	locateNewNumber();
	iterationCounter++;
	
	moveOtonomicObjects(false);

	for (list<Player*>::iterator it = players->begin(); it != players->end(); ++it)
	{
		Player *player = *it;
		if (player->getIsAlive())
		{
			for (list<char>::const_iterator key = keyHits.begin(); key != keyHits.end(); key++)
			{
				player->inputKey(*key);
			}
			player->move();

			if (iterationCounter % 200 == 0)
			{
				player->addBullet();
			}
		}
	}
}

void TheMathGame::doSubIteration()
{
	moveOtonomicObjects(true);
}

void TheMathGame::locateNewNumber()
{
	bool foundNewPlace = false;
	int triesCount = 1;

	while (!foundNewPlace && triesCount < 10)
	{
		int randRow = rand() % screenHight;
		int randCol = rand() % screenLength;

		if (isAreaEmpty(randRow, randCol))
		{
			int newNumber = rand() % getDifficultyLevel() + 1;  

			if (newNumber < 9 || randCol != screenLength - 1)
			{
				NumberScreenObject *newNumberScreenObject = new NumberScreenObject(screen, randRow, randCol, screenHight, screenLength, newNumber);
				newNumberScreenObject->printToScreen();
				foundNewPlace = true;
			}
		}

		triesCount++;
	}
}
bool TheMathGame::isAreaEmpty(int row, int col)
{
	if (screen[row][col] != NULL)
	{
		return false;
	}
	else if (row > 0 && screen[row - 1][col] != NULL)
	{
		return false;
	}
	else if (col > 0 && screen[row][col - 1] != NULL)
	{
		return false;
	}
	else if (row < screenHight - 1 && screen[row + 1][col] != NULL)
	{
		return false;
	}
	else if (col < screenLength - 1 && screen[row][col + 1] != NULL)
	{
		return false;
	}

	return true;
}

void TheMathGame::initScreen()
{
	screen = new ScreenObject**[screenHight];
	for (int i = 0; i < screenHight; i++)
	{
		screen[i] = new ScreenObject*[screenLength];

		for (int j = 0; j < screenLength; j++)
		{
			screen[i][j] = NULL;
		}
	}
}

void TheMathGame::drawBorder() const
{
	if (GAME_SCREEN_START_ROW > 0)
	{
		for (int i = 0; i < screenLength; i++)
		{
			gotoxy(i, GAME_SCREEN_START_ROW - 1);
			cout << BORDER_CHAR;
		}
	}
}
void TheMathGame::drawScreen() const
{
	for (int i = 0; i < screenHight; i++)
	{
		for (int j = 0; j < screenLength; j++)
		{
			gotoxy(j, GAME_SCREEN_START_ROW + i);

			if (screen[i][j] != NULL)
			{
				cout << screen[i][j]->getScreenString();
			}
		}
	}
}

	// END of NEW CODE EX1