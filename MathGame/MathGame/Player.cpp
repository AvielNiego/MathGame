//NEW CODE EX1, author=Aviel Niego 203839170, date=<2015-03-20>

#include "Player.h"
#include "Shot.h"
#include "Exercise.h"
#include "SmallExercise.h"

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

void Player::shot()
{
	Direction::value shotDirection = (movingDir == Direction::STAY ? Direction::UP : movingDir);
	new Shot(screen, locationRow, locationCol, screenHight, screenLength, shotDirection);
}

void Player::moveToStartPoint()
{
	// If we are not going to override a player
	if (dynamic_cast<Player*>(screen[startLocationRow][startLocationCol]) == NULL)
	{
		cleanFromScreen();
		delete screen[startLocationRow][startLocationCol];
		screen[startLocationRow][startLocationCol] = this;
		locationCol = startLocationCol;
		locationRow = startLocationRow;
		printToScreen();
	}
}

void Player::shotKill()
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
			if (shotBeside != NULL)
			{
				shotBeside->kill();
				shotKill();
			}
		}
	}
}

Player::Player(char playerSighn, char dirUp, char dirLeft, char dirDown, char dirRight, char shotKey, ScreenObject*** screen, int screenHight, int screenLength, int startLocationRow, int startLocationCol, int lifeRow, int lifeCol, bool isEquationStraightenedWithLife):
	GameEntities(screen, startLocationRow, startLocationCol, screenHight, screenLength),
	playerSighn(playerSighn), dirUp(dirUp), dirLeft(dirLeft), dirDown(dirDown), dirRight(dirRight), 
	isWon(false), isAlive(true), lifeRow(lifeRow), lifeCol(lifeCol), isEquationStraightenedWithLife(isEquationStraightenedWithLife), levelsWonCount(0),
	movingDir(Direction::STAY), startLocationRow(startLocationRow), startLocationCol(startLocationCol), shotKey(shotKey)
{}

void Player::initPlayerForNewLevel(int maximumNumber)
{
	cleanFromScreen();
	removeFromScreen();

	locationRow = startLocationRow;
	locationCol = startLocationCol;
	screen[locationRow][locationCol] = this;
	printToScreen();

	exercise = SmallExercise::generateExercise(maximumNumber);
	isAlive = true;
	isWon = false;
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