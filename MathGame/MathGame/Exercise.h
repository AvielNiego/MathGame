//NEW CODE EX1, author=Aviel Niego 203839170, date=<2015-03-20>

#ifndef _EXERCISE_H_
#define _EXERCISE_H_

#include "MathAction.h"
#include <string>
#include "Exercise.h"
#include <iostream>
#include "io_utils.h"
#include "StringUtils.h"
#include <string>

using namespace std;

class Exercise
{
protected:
	static const int MATH_OPERATORS_COUNT = 4;

	// Members should not be changed after initial, so there are not any setters and no empty constructor
	bool isExerciseSolved;

	// No copy constructor
	Exercise(Exercise &e){}

	// New instance sould be created with generateExercise(int maximumNumber)
	Exercise():isExerciseSolved(false){}

	static MathAction generateRandomMathOperator()
	{
		return MathAction(rand() % MATH_OPERATORS_COUNT);
	}
public:
	static const int MAX_EXERCISE_SIZE = 20;

	virtual bool insertNumber(int number) =0;

	virtual bool exerciseSolved() const
	{
		return isExerciseSolved;
	}

	/*
	Returns TRUE if the assignment succeed, FALSE otherwise.
	*/
	virtual string toExerciseString() =0;
};

#endif

// END of NEW CODE EX1