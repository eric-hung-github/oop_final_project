#include "Postition.h"

Position::Position()
{
	this->x = 0;
	this->y = 0;
}

Position::Position(int x, int y)
{
	this->x = x;
	this->y = y;
}

Position& Position::operator+(const Position& pos)
{
	Position rePos;
	rePos.x = this->x + pos.x;
	rePos.y = this->y + pos.y;
	return rePos;
}

Position& Position::operator-(const Position& pos)
{
	Position rePos;
	rePos.x = this->x - pos.x;
	rePos.y = this->y - pos.y;
	return rePos;
}

bool Position::operator==(const Position& pos)
{
	if (this->x == pos.x && this->y == pos.y) { return true; }
	else { return false; }
}

Position Position::direction(char c)
{
	switch (c)
	{
	case 'w':
		return dirUp;
	case 'a':
		return dirLeft;
	case 's':
		return dirDown;
	case'd':
		return dirRight;
	default:
		return Position(0, 0);
	}
}