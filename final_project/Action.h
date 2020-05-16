#pragma once
#include <vector>
#include "Being.h"
#include "Postition.h"

class Action
{
public:
	Action(int point);

	int point;
	virtual void execute(Being being);
};

class ActAttack :public Action
{
public:
	int range;

	ActAttack(int point, int range) :Action::Action(point) { this->range = range; }

	//
	void execute (Being being)override;
};

class ActSheild :public Action
{
public:
	ActSheild(int point) :Action::Action(point) {}

	void execute(Being being)override;
};

class ActMove :public Action
{
public:
	ActMove(int point) :Action::Action(point) {}


	vector<Postition> direction;
	void execute(Being being)override;
};

class ActHeal :public Action
{
public:
	ActHeal(int point) :Action::Action(point) {}

	void execute(Being being)override;
};

class ActRest :public Action
{
public:
	//ActRest(int point) :Action::Action(point) {}

	void execute(Being being)override;
};