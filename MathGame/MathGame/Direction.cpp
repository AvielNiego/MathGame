#include "Direction.h"

Direction::value Direction::getOppositeDirection(Direction::value dir)
{
	switch (dir)
	{
	case Direction::UP: return Direction::DOWN;
	case Direction::RIGHT: return Direction::LEFT;
	case Direction::DOWN: return Direction::UP;
	case Direction::LEFT: return Direction::RIGHT;
	case Direction::STAY: return Direction::STAY;
	default: return Direction::STAY;
	}
}