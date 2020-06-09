#include "Action.h"

#include "Being.h"// waring : Forward Declartion

Action::Action()
{
	this->point = 0;
}

Action::Action(int point)
{
	this->point = point;
}

void Action::execute(Being *being)
{
}

ActMove::ActMove(int point, string steps)
{
	this->point = 0;
	this->steps = steps;
}

// attack
void ActAttack::execute(Being *being)
{
	being->attack(this);
}

// sheild
void ActSheild::execute(Being *being)
{
	being->sheild(this);
}

// move
void ActMove::execute(Being *being)
{
	being->move(this);
}

// heal
void ActHeal::execute(Being *being)
{
	being->heal(this);
}

// long rest
void ActRest::execute(Being *being)
{
	being->longRest();
}


