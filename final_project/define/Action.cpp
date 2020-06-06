#include "Action.h"

// attack
void ActAttack::execute(Being being)
{

}

// sheild
void ActSheild::execute(Being being)
{
	
}

ActMove::ActMove(int point,string steps)
{
	this->point = 0;
	this->steps = steps;
}

// move
void ActMove::execute(Being being)
{
}

// heal
void ActHeal::execute(Being being)
{
    if(being.hp+point<=being.maxhp)
        being.hp+=point;
    else
        being.hp=being.maxhp;
}

// long rest
void ActRest::execute(Being being)
{
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
void Action::execute(Being being)
{
}
