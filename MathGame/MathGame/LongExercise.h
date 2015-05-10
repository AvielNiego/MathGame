//NEW CODE EX1, author=Aviel Niego 203839170, date=<2015-05-01>

#ifndef _LONG_EXERCISE_H_
#define _LONG_EXERCISE_H_

#include "Exercise.h"
#include <list>
#include <algorithm>

class LongExercise :
	public Exercise
{
	static const int MAX_NUMBER = 21;

	MathAction firstExerOperator, secondExerOperator;
	int variables[4];
	int varPosition1, varPosition2;
	bool isHalfSolved;

public:

	void initVarPositions(int var1, int var2, int var3, int result);

	LongExercise(int var1, MathAction first_exer_operator, int var2, MathAction second_exer_operator, int var3, int result);

	int indexOf(int* a, int size, int value);

	static bool isEnlargerAction(MathAction firstExerOperator);
	static int getRandomNumber();
	static bool isPlusMinus(MathAction secondExerOperator);
	static bool isMulDiv(MathAction firstExerOperator);
	static void generateDiv(int &randNum1, int &randNum2);
	static void generateMinus(int &randNum1, int &randNum2);
	static int generateExerWithTwoNumbers(MathAction firstExerOperator, int &randNum1, int &randNum2);
	static int getRandomNumber(int firstResult);
	static void generateExerWithTwoNumbersAndResult(MathAction firstExerOperator, int firstResult, int& randNum1, int& randNum2);
	static LongExercise* generateExercise(int maximumNumber);
	double calc(MathAction exerOperator, double var1, double var2);
	double reverseCalc(MathAction exerOperator, double var1, double var2);
	bool insertNumber(int number) override;
	bool solveExersiceWithValAt1();
	bool solveExersiceWithValAt2();
	bool solveExersiceWithValAt3();
	bool solveExersiceWithValAt4();
	bool isLegitResult(double result);
	string getVarString(int i);
	virtual string toExerciseString() override;
	char getOperatorChar(MathAction exerOperator);
};

#endif
// END of NEW CODE EX1
