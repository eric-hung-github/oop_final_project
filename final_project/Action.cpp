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

void Action::execute(Being* being)
{
}

ActMove::ActMove(int point, string steps)
{
	this->point = 0;
	this->steps = steps;
}

// attack
void ActAttack::execute(Being* being)
{
	cout << being->name << " attack: " << this->point << " range " << this->range << endl;
	being->attack(*this);
}

// sheild
void ActSheild::execute(Being* being)
{
	cout << being->name << " shield: " << this->point << endl;
	being->sheild(*this);
}

// move
void ActMove::execute(Being* being)
{
	if (this->steps != "")
	{
		cout << being->name << " move: " << this->steps << endl;
	}
	else
	{

		cout << being->name << " move: " << this->point << endl;
	}
	being->move(*this);
}

// heal
void ActHeal::execute(Being* being)
{
	cout << being->name << " heal: " << this->point << endl;
	being->heal(*this);
}

// long rest
void ActRest::execute(Being* being)
{
	cout << being->name << " rest: " << this->point << endl;
	being->longRest();
}


