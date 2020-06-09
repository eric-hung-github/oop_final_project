#include "Being.h"

void Being::heal(Action *action)
{
	if (this->hp + action->point <= this->maxHp) {
		this->hp += action->point;
	}
	else {
		this->hp = this->maxHp;
	}
}

void Being::sheild(Action* action)
{
	this->sheldPoint += action->point;
}

void Being::move(Action *action)
{
}

void Being::attack(Action *action)
{
}

void Being::longRest()
{
}
