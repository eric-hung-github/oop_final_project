#include "Being.h"

void Being::heal(ActHeal action)
{
	if (this->hp + action.point <= this->maxHp) {
		this->hp += action.point;
	}
	else {
		this->hp = this->maxHp;
	}
}

void Being::sheild(ActSheild action)
{
	this->sheldPoint += action.point;
}

void Being::move(ActMove action)
{
}

void Being::attack(ActAttack action)
{
}

void Being::longRest()
{
}
