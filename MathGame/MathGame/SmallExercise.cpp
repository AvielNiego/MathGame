//NEW CODE EX1, author=Aviel Niego 203839170, date=<2015-05-09>

#include "SmallExercise.h"
#include <iostream>
#include "io_utils.h"
#include "StringUtils.h"
#include <string>
#include "Exercise.h"

using namespace std;

SmallExercise* SmallExercise::generateExercise(int maximumNumber)
{
	int randNum1 = rand() % maximumNumber + 1;
	int randNum2 = rand() % maximumNumber + 1;

	int varPosition = 0;

	string a = "var1 * var2 - var3 = var4";

	MathAction exerOperator = generateRandomMathOperator();
	switch (exerOperator)
	{
	case PLUS:
		varPosition = rand() % 2 + 1;
		return new SmallExercise(randNum1, randNum2, randNum1 + randNum2, varPosition, exerOperator);
	case MINUS:
		// varPosition can be 2 or 3
		varPosition = rand() % 2 + 2;
		return new SmallExercise(randNum2 + randNum1, randNum1, randNum2, varPosition, exerOperator);
	case MUL:
		varPosition = rand() % 2 + 1;
		return new SmallExercise(randNum1, randNum2, randNum1 * randNum2, varPosition, exerOperator);
	case DIV:
		// varPosition can be 2 or 3
		varPosition = rand() % 2 + 2;
		return new SmallExercise(randNum2 * randNum1, randNum1, randNum2, varPosition, exerOperator);
	default:
		return NULL;
	}
}

char SmallExercise::getOperatorChar()
{
	switch (exerOperator)
	{
	case PLUS:
		return '+';
	case MINUS:
		return '-';
	case MUL:
		return '*';
	case DIV:
		return '/';
	default:
		return 0;
	}
}

/*
Returns TRUE if the assignment succeed, FALSE otherwise.
*/
bool SmallExercise::setVarPosition(int varPosition)
{
	if (validateVarPosition(varPosition))
	{
		this->varPosition = varPosition;
		return true;
	}
	else
	{
		return false;
	}
}

string SmallExercise::toEquationString()
{
	return StringUtils::toString(firstNumber) + ' ' + getOperatorChar() + ' ' + StringUtils::toString(secondNumber) + ' ' + '=' + ' ' + StringUtils::toString(result);
}

string SmallExercise::toExerciseString()
{
	const string VAR_STRING = "__";

	switch (varPosition)
	{
	case 1:
		return VAR_STRING + ' ' + getOperatorChar() + ' ' + StringUtils::toString(secondNumber) + ' ' + '=' + ' ' + StringUtils::toString(result);
	case 2:
		return StringUtils::toString(firstNumber) + ' ' + getOperatorChar() + ' ' + VAR_STRING + ' ' + '=' + ' ' + StringUtils::toString(result);
	case 3:
		return StringUtils::toString(firstNumber) + ' ' + getOperatorChar() + ' ' + StringUtils::toString(secondNumber) + ' ' + '=' + ' ' + VAR_STRING;
	default:
		return NULL;
	}
}

bool SmallExercise::validateVarPosition(int varPosition)
{
	if (varPosition == 1 || varPosition == 2 || varPosition == 3)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int SmallExercise::getVariable()
{
	if (varPosition == 1)
	{
		return firstNumber;
	}
	else if (varPosition == 2)
	{
		return secondNumber;
	}
	else if (varPosition == 3)
	{
		return result;
	}

	return -1;
}

bool SmallExercise::insertNumber(int number)
{
	bool isLegitimateNumberToEat = (number == getVariable());

	isExerciseSolved = isLegitimateNumberToEat;
	return isLegitimateNumberToEat;
}

// END of NEW CODE EX1