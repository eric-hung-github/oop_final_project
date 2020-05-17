#include "Action.h"

// attack
void ActAttack::execute(Being being)
{

}

// sheild
void ActSheild::execute(Being being)
{
}

// move
void ActMove::execute(Being being)
{
}

// heal
void ActHeal::execute(Being being)
{
}

// long rest
void ActRest::execute(Being being)
{
}

Action::Action(int point)
{
	this->point = point;
}

// virtual function
void Action::execute(Being being)
{
}
