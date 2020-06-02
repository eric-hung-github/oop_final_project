#include "Monster.h"

Monster::Monster()
{
	this->hp = 0;
	this->maxHp = this->hp;
	this->atk = 0;
	this->range = 0;
	this->sheldPoint = 0;
}

Monster::Monster(int hp, int atk, int range)
{
	this->hp = hp;
	this->maxHp = this->hp;
	this->atk = atk;
	this->range = range;
	this->sheldPoint = 0;
}
