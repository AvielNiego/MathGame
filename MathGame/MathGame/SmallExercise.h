#ifndef _SMALL_EXERCISE_H_
#define _SMALL_EXERCISE_H_

#include "Exercise.h"
class SmallExercise :
	public Exercise
{

	// Members should not be changed after initial, so there are not any setters and no empty constructor
	int firstNumber, secondNumber, result;
	int varPosition;

	MathAction exerOperator;

	// No copy constructor
	SmallExercise(Exercise &e){}

	// New instance sould be created with generateExercise(int maximumNumber)
	SmallExercise(int first_number, int second_number, int result, int var_position, MathAction exer_operator)
		: firstNumber(first_number),
		  secondNumber(second_number),
		  result(result),
		  varPosition(var_position),
		  exerOperator(exer_operator)
	{
		if (!setVarPosition(varPosition))
		{
			this->varPosition = -1;
		}
	}

public:
	static SmallExercise* generateExercise(int maximumNumber);
	bool insertNumber(int number);

	bool exerciseSolved() const
	{
		return isExerciseSolved;
	}

	char getOperatorChar();

	/*
	Returns TRUE if the assignment succeed, FALSE otherwise.
	*/
	bool setVarPosition(int varPosition);

	string toEquationString();

	string toExerciseString();


private:
	bool validateVarPosition(int varPosition);
	int getVarPosition(){ return varPosition; }
	int getVariable();
};

#endif // !_SMALL_EXERCISE
