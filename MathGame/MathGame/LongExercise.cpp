//NEW CODE EX1, author=Aviel Niego 203839170, date=<2015-05-09>

#include "LongExercise.h"
#include "StringUtils.h"

void LongExercise::initVarPositions(int var1, int var2, int var3, int result)
{
	int ints[] = { var1, var2, var3, result };
	int sortedInts[] = { var1, var2, var3, result };
	sort(sortedInts, sortedInts + 4);

	varPosition1 = indexOf(ints, 4, sortedInts[0]);
	varPosition2 = indexOf(ints, 4, sortedInts[1]);

	if (varPosition1 == varPosition2)
	{
		varPosition2++;
	}
	else if (varPosition1 > varPosition2)
	{
		swap(varPosition1, varPosition2);
	}

	variables[varPosition1] = -1;
	variables[varPosition2] = -1;
}

LongExercise::LongExercise(int var1, MathAction first_exer_operator, int var2, MathAction second_exer_operator, int var3, int result): firstExerOperator(first_exer_operator),
                                                                                                                                       secondExerOperator(second_exer_operator),
                                                                                                                                       isHalfSolved(false)
{
	variables[0] = var1;
	variables[1] = var2;
	variables[2] = var3;
	variables[3] = result;
	initVarPositions(var1, var2, var3, result);
}

int LongExercise::indexOf(int* a, int size, int value)
{
	for (int i = 0; i < size; ++i)
	{
		if (a[i] == value)
		{
			return i;
		}
	}

	return -1;
}

bool LongExercise::isEnlargerAction(MathAction exerOperator)
{
	return exerOperator == MathAction::PLUS || exerOperator == MathAction::MUL;
}


int LongExercise::getRandomNumber()
{
	return rand() % MAX_NUMBER + 1;
}

bool LongExercise::isPlusMinus(MathAction exerOperator)
{
	return exerOperator == MathAction::PLUS || exerOperator == MathAction::MINUS;
}


bool LongExercise::isMulDiv(MathAction firstExerOperator)
{
	return firstExerOperator == MathAction::MUL || firstExerOperator == MathAction::DIV;
}

void LongExercise::generateDiv(int &randNum1, int &randNum2)
{
	randNum2 = getRandomNumber();
	randNum1 = getRandomNumber() * randNum2;
}

void LongExercise::generateMinus(int &randNum1, int &randNum2)
{
	randNum2 = getRandomNumber();
	randNum1 = getRandomNumber() + randNum2;
}

int LongExercise::generateExerWithTwoNumbers(MathAction firstExerOperator, int &randNum1, int &randNum2)
{
	switch (firstExerOperator)
	{
	case PLUS:
		randNum2 = getRandomNumber();
		randNum1 = getRandomNumber();
		return randNum1 + randNum2;
	case MUL:
		randNum2 = getRandomNumber();
		randNum1 = getRandomNumber();
		return randNum1 * randNum2;
	case MINUS: 
		generateMinus(randNum1, randNum2);
		return randNum1 - randNum2;
	case DIV: 
		generateDiv(randNum1, randNum2);
		return randNum1 / randNum2;
	default:
		return -1;
	}
}

int LongExercise::getRandomNumber(int maximum)
{
	return (rand() % (MAX_NUMBER < maximum ? MAX_NUMBER : maximum)) + 1;
}

void LongExercise::generateExerWithTwoNumbersAndResult(MathAction exerOperator, int firstResult, int& randNum1, int& randNum2)
{
	int i;
	switch (exerOperator)
	{
	case PLUS: 
		randNum2 = getRandomNumber(firstResult);
		randNum1 = firstResult - randNum2;
		break;
	case MINUS: 
		randNum2 = getRandomNumber();
		randNum1 = firstResult + randNum2;
		break;
	case MUL:
		randNum2 = getRandomNumber(firstResult);

		i=0;
		while (firstResult % randNum2 != 0 && i < 10)
		{
			randNum2 = getRandomNumber(firstResult);
			i++;
		}
		if (firstResult % randNum2 != 0)
		{
			randNum2 = 1;
		}

		randNum1 = firstResult / randNum2;
		break;
	case DIV: 
		randNum2 = getRandomNumber();
		randNum1 = firstResult * randNum2;
		break;
	default: break;
	}
}


double LongExercise::calc(int randNum1, MathAction firstExerOperator, int randNum2, MathAction secondExerOperator, int randNum3)
{
	double result;
	if (isMulDiv(firstExerOperator) || isPlusMinus(secondExerOperator))
	{
		double firstResult = calc(firstExerOperator, randNum1, randNum2);
		result = calc(secondExerOperator, firstResult, randNum3);
	}
	else
	{
		double firstResult = calc(secondExerOperator, randNum2, randNum3);
		result = calc(firstExerOperator, randNum1, firstResult);
	}

	return result;
}

LongExercise* LongExercise::generateExercise()
{
	MathAction firstExerOperator = generateRandomMathOperator();
	MathAction secondExerOperator = generateRandomMathOperator();

	if (isEnlargerAction(firstExerOperator) && isEnlargerAction(secondExerOperator))
	{
		int randNum1 = getRandomNumber();
		int randNum2 = getRandomNumber();
		int randNum3 = getRandomNumber();

		double result = calc(randNum1, firstExerOperator, randNum2, secondExerOperator, randNum3);

		return new LongExercise(randNum1, firstExerOperator, randNum2, secondExerOperator, randNum3, result);
	}
	
	if (isMulDiv(firstExerOperator) || isPlusMinus(secondExerOperator))
	{
		if (isEnlargerAction(secondExerOperator))
		{
			int randNum1, randNum2;
			generateExerWithTwoNumbers(firstExerOperator, randNum1, randNum2);
			int randNum3 = getRandomNumber();

			double result = calc(randNum1, firstExerOperator, randNum2, secondExerOperator, randNum3);

			return new LongExercise(randNum1, firstExerOperator, randNum2, secondExerOperator, randNum3, result);
		}
		
		int randomResult = getRandomNumber();
		int randNum3 = getRandomNumber();

		int firstResult = (secondExerOperator == MathAction::DIV) ? randomResult * randNum3 : randomResult + randNum3;
		int randNum1, randNum2;

		generateExerWithTwoNumbersAndResult(firstExerOperator, firstResult, randNum1, randNum2);

		return new LongExercise(randNum1, firstExerOperator, randNum2, secondExerOperator, randNum3, randomResult);
	}
	else
	{
		if (isEnlargerAction(firstExerOperator))
		{
			int randNum2, randNum3;
			generateExerWithTwoNumbers(firstExerOperator, randNum2, randNum3);
			int randNum1 = getRandomNumber();

			double result = calc(randNum1, firstExerOperator, randNum2, secondExerOperator, randNum3);

			return new LongExercise(randNum1, firstExerOperator, randNum2, secondExerOperator, randNum3, result);
		}

		if (firstExerOperator == MathAction::MINUS)
		{
			int randResult = getRandomNumber();
			int randNum2, randNum3;
			int randNum1 = generateExerWithTwoNumbers(secondExerOperator, randNum2, randNum3) + randResult;
			return new LongExercise(randNum1, firstExerOperator, randNum2, secondExerOperator, randNum3, randResult);
		}
	}

	return nullptr;
}

double LongExercise::calc(MathAction exerOperator, double var1, double var2)
{
	double result;
	switch (exerOperator)
	{
	case PLUS: 
		result = var1 + var2;
		break;
	case MINUS: 
		result = var1 - var2;
		break;
	case MUL: 
		result = var1 * var2;
		break;
	case DIV: 
		result = var1 / var2;
		break;
	}

	return result;
}

double LongExercise::reverseCalc(MathAction exerOperator, double var1, double var2)
{
	double result;
	switch (exerOperator)
	{
	case PLUS:
		result = var1 - var2;
		break;
	case MINUS:
		result = var1 + var2;
		break;
	case MUL:
		result = var1 / var2;
		break;
	case DIV:
		result = var1 * var2;
		break;
	}

	return result;
}

bool LongExercise::insertNumber(int number)
{

	if (isHalfSolved)
	{
		variables[varPosition2] = number;
		double result;

		if (isMulDiv(firstExerOperator) || isPlusMinus(secondExerOperator))
		{
			double firstResult = calc(firstExerOperator, variables[0], variables[1]);
			result = calc(secondExerOperator, firstResult, variables[2]);
		}
		else
		{
			double firstResult = calc(secondExerOperator, variables[1], variables[2]);
			result = calc(firstExerOperator, variables[0], firstResult);
		}

		if (result == variables[3])
		{
			isExerciseSolved = true;
			return true;
		}
		else
		{
			variables[varPosition2] = -1;
			return false;
		}
	}
	else
	{
		variables[varPosition1] = number;

		bool isLegitNumber = false;
		switch (varPosition2)
		{
		case 0:
			isLegitNumber = solveExersiceWithValAt1();
			break;
		case 1:
			isLegitNumber = solveExersiceWithValAt2();
			break;
		case 2:
			isLegitNumber = solveExersiceWithValAt3();
			break;
		case 3:
			isLegitNumber = solveExersiceWithValAt4();
			break;
		}

		if (isLegitNumber)
		{
			isHalfSolved = true;
			return true;
		}
		else
		{
			variables[varPosition2] = -1;
			return false;
		}
	}
}

bool LongExercise::solveExersiceWithValAt1()
{
	double result;
	if (isMulDiv(firstExerOperator) || isPlusMinus(secondExerOperator))
	{
		double firstResult = reverseCalc(secondExerOperator, variables[3], variables[2]);
		result = reverseCalc(firstExerOperator, firstResult, variables[1]);
	}
	else
	{
		double firstResult = calc(secondExerOperator, variables[1], variables[2]);
		result = reverseCalc(firstExerOperator, variables[3], firstResult);
	}
	return isLegitResult(result);
}

bool LongExercise::isLegitResult(double result)
{
	double floor = std::floor(result);
	return (result > 0 && result == floor && result < 22);
}

bool LongExercise::solveExersiceWithValAt2()
{
	MathAction firstAction = (isPlusMinus(firstExerOperator) ? MINUS : DIV);
	double firstResult = calc(firstAction, variables[3], variables[0]);

	double finalResult = reverseCalc(secondExerOperator, firstResult, variables[2]);

	if (firstExerOperator == MINUS)
	{
		firstResult = firstResult * (-1);
	}
	if (firstExerOperator == DIV)
	{
		pow(finalResult, -1);
	}

	return isLegitResult(finalResult);
}

bool LongExercise::solveExersiceWithValAt3()
{
	MathAction firstAction = (isPlusMinus(firstExerOperator) ? MINUS : DIV);
	double firstResult = calc(firstAction, variables[3], variables[0]);
	
	double finalResult = 0;
	if (isPlusMinus(secondExerOperator))
	{
		switch (firstExerOperator)
		{
		case PLUS: 
			finalResult = calc(MINUS, firstResult, variables[1]);
			break;
		case MINUS: 
			finalResult = calc(PLUS, firstResult, variables[1]);
			break;
		case MUL: 
			finalResult = calc(MINUS, firstResult, variables[1]);
			break;
		case DIV: 
			finalResult = calc(MUL, firstResult, variables[1]) - 1;
			break;
		}

		if (secondExerOperator == MINUS)
		{
			finalResult = firstResult * (-1);
		}
	}
	else
	{
		switch (firstExerOperator)
		{
		case PLUS:
			finalResult = calc(DIV, firstResult, variables[1]);
			break;
		case MINUS:
			finalResult = calc(DIV, firstResult, variables[1] * (-1));
			break;
		case MUL:
			finalResult = calc(DIV, firstResult, variables[1]);
			break;
		case DIV:
			finalResult = calc(MUL, firstResult, variables[1]);
			break;
		}

		if (secondExerOperator == DIV)
		{
			pow(finalResult, -1);
		}
	}

	return isLegitResult(finalResult);
}

bool LongExercise::solveExersiceWithValAt4()
{
	double result;

	if (isMulDiv(firstExerOperator) || isPlusMinus(secondExerOperator))
	{
		double firstResult = calc(firstExerOperator, variables[0], variables[1]);
		result = calc(secondExerOperator, firstResult, variables[2]);
	}
	else
	{
		double firstResult = calc(secondExerOperator, variables[1], variables[2]);
		result = calc(firstExerOperator, variables[0], firstResult);
	}

	return isLegitResult(result);
}

string LongExercise::getVarString(int i)
{
	return variables[i] != -1 ? StringUtils::toString(variables[i]) : "__";
}

string LongExercise::toExerciseString()
{
	return getVarString(0) + getOperatorChar(firstExerOperator) + getVarString(1) + getOperatorChar(secondExerOperator) + getVarString(2) + " = " + getVarString(3);
}

char LongExercise::getOperatorChar(MathAction exerOperator)
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

// END of NEW CODE EX1