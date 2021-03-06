//NEW CODE EX1, author=Aviel Niego 203839170, date=<2015-03-20>

#include "Player.h"
#include "Shot.h"
#include "Exercise.h"
#include "SmallExercise.h"
#include "LongExercise.h"
#include "Creature.h"
#include "NumberEater.h"

Direction::value Player::getKeyDirection(char keyPressed)
{
	if (keyPressed == dirUp)
	{
		return Direction::UP;
	}
	else if (keyPressed == dirLeft)
	{
		return Direction::LEFT;
	}
	else if (keyPressed == dirDown)
	{
		return Direction::DOWN;
	}
	else if (keyPressed == dirRight)
	{
		return Direction::RIGHT;
	}

	return movingDir;
}

void Player::printLife()const
{
	gotoxy(lifeCol, lifeRow);
	cout << "      ";

	for (int i = 0; i < life; i++)
	{
		gotoxy(lifeCol + i, lifeRow);
		cout << LIFE_CHAR;
	}

	cout << ' ' << getPoints();
}

void Player::printExercise()const
{
	string strExercise = exercise->toExerciseString();
	int startCol, startDeleteCol;

	if (!isEquationStraightenedWithLife)
	{
		startCol = (lifeCol + 3) - strExercise.length();
		startDeleteCol = (lifeCol + 3) - Exercise::MAX_EXERCISE_SIZE;
	}
	else
	{
		startCol = lifeCol;
		startDeleteCol = lifeCol;
	}

	// Delete previous exercise
	for (int i = 0; i < Exercise::MAX_EXERCISE_SIZE; i++)
	{
		gotoxy(startDeleteCol + i, lifeRow + 1);
	}

	gotoxy(startCol, lifeRow + 1);
	cout << strExercise;
}

void Player::kill()
{
	life--;
	printLife();

	if (life == 0)
	{
		isAlive = false;
		cleanFromScreen();
		removeFromScreen();
	}
}

void Player::printExtra() const
{
	printLife();
	printExercise();
}

void Player::addBullet()
{
	stack++;
}

void Player::shot()
{
	if (stack > 0)
	{
		Direction::value shotDirection = (movingDir == Direction::STAY ? Direction::UP : movingDir);
		new Shot(screen, locationRow, locationCol, screenHight, screenLength, shotDirection);
		stack--;
	}
}

void Player::moveToStartPoint()
{
	// If we are not going to override a player
	if (dynamic_cast<Player*>(screen[startLocationRow][startLocationCol]) == NULL)
	{
		cleanFromScreen();
		screen[locationRow][locationCol] = NULL;
		delete screen[startLocationRow][startLocationCol];
		screen[startLocationRow][startLocationCol] = this;
		locationCol = startLocationCol;
		locationRow = startLocationRow;
		printToScreen();
	}
}

void Player::respawnKill()
{
	movingDir = Direction::STAY;
	kill();

	if (isAlive)
	{
		moveToStartPoint();
	}
}

void Player::inputKey(char keyPressed)
{
	if (keyPressed == shotKey)
	{
		shot();
	}
	else
	{
		movingDir = getKeyDirection(keyPressed);
	}
}

void Player::move()
{
	ScreenObject* screenObjectBeside = getObjectAt(movingDir);

	if (screenObjectBeside == NULL)
	{
		moveTo(movingDir);
	}
	else
	{
		int numberEaten = eatNumber(screenObjectBeside);
		// If the number beside is number and we have successfully eaten him
		if (numberEaten != -1)
		{
			moveTo(movingDir);
			if (exercise->insertNumber(numberEaten))
			{
				printExercise();
				if (exercise->exerciseSolved())
				{
					isWon = true;
					levelsWonCount++;
				}
			}
			else
			{
				kill();
			}
		}
		else
		{
			// If the object beside is otonomicObject
			Shot* shotBeside = dynamic_cast<Shot*>(screenObjectBeside);
			Creature* creatureBeside = dynamic_cast<Creature*>(screenObjectBeside);
			if (shotBeside != NULL)
			{
				shotBeside->kill();
				respawnKill();
			}
			else if (creatureBeside != NULL)
			{
				if (dynamic_cast<NumberEater*>(screenObjectBeside) != NULL)
				{
					moveTo(movingDir);
					creatureBeside->kill();
				}
				else
				{
					kill();
				}
			}
		}
	}
}

Player::Player(char playerSighn, char dirUp, char dirLeft, char dirDown, char dirRight, char shotKey, ScreenObject*** screen, int screenHight, int screenLength, int startLocationRow, int startLocationCol, int lifeRow, int lifeCol, bool isEquationStraightenedWithLife):
	GameEntities(screen, startLocationRow, startLocationCol, screenHight, screenLength),
	playerSighn(playerSighn), dirUp(dirUp), dirLeft(dirLeft), dirDown(dirDown), dirRight(dirRight), 
	isWon(false), isAlive(true), lifeRow(lifeRow), lifeCol(lifeCol), isEquationStraightenedWithLife(isEquationStraightenedWithLife), levelsWonCount(0),
	movingDir(Direction::STAY), startLocationRow(startLocationRow), startLocationCol(startLocationCol), shotKey(shotKey), stack(START_STACK)
{}

void Player::initPlayerForNewLevel(int maximumNumber)
{
	cleanFromScreen();
	removeFromScreen();

	locationRow = startLocationRow;
	locationCol = startLocationCol;
	screen[locationRow][locationCol] = this;
	printToScreen();

	if (maximumNumber < 21)
	{
		exercise = SmallExercise::generateExercise(maximumNumber);
	}
	else
	{
		exercise = LongExercise::generateExercise();
	}

	isAlive = true;
	isWon = false;
	stack = START_STACK;
	movingDir = Direction::STAY;
	life = START_LIFE;
	printLife();
	printExercise();
}

string Player::getScreenString() const
{
	stringstream ss;
	ss << playerSighn;
	string screenString;
	ss >> screenString;
	return screenString;
}

// END of NEW CODE EX1