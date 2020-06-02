#include "Action.h"
#include "Character.h"

// attack
void ActAttack::execute(Being *being)
{

}

// sheild
void ActSheild::execute(Being *being)
{
	being->sheldPoint += this->point;
}

ActMove::ActMove(int point,string steps)
{
	this->point = 0;
	this->steps = steps;
}

// move
void ActMove::execute(Being *being)
{
}

// heal
void ActHeal::execute(Being *being)
{
	if (being->hp + this->point <= being->maxHp) {
		being->hp += this->point;
	}
	else {
		being->hp = being->maxHp;
	}
}

// long rest
void ActRest::execute(Being *being)
{
	being->longRest();
}

Action::Action()
{
	this->point = 0;
}

Action::Action(int point)
{
	this->point = point;
}

// virtual function
void Action::execute(Being *being)
{

}
