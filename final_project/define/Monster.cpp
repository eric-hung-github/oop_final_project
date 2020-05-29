#include "Monster.h"

Monster::Monster()
{
	this->hp = 0;
	this->atk = 0;
	this->range = 0;
}

Monster::Monster(int hp, int atk, int range)
{
	this->hp = hp;
	this->atk = atk;
	this->range = range;
}
