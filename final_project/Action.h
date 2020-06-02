#pragma once

#include <iostream>
#include <vector>

#include "Postition.h"

class Being;// waring : Forward Declartion

class Action
{
public:
	Action();
	Action(int point);

	int point;
	virtual void printAct() {}
	virtual void execute(Being *being);
};

class ActAttack :public Action
{
public:
	int range;

	ActAttack(int point, int range) :Action::Action(point) { this->range = range; }

	//
	void execute(Being *being)override;
	void printAct()override { cout << " attack " << this->point; };
};

class ActSheild :public Action
{
public:
	ActSheild(int point) :Action::Action(point) {}

	void execute(Being *being)override;
	void printAct()override { cout << " shelid " << this->point; };
};

class ActMove :public Action
{
public:
	string steps;

	ActMove(int point) :Action::Action(point) {}
	ActMove(int point, string steps);


	void execute(Being *being)override;
	void printAct()override { (point) ? cout << " move " << this->point : cout << " move " << this->steps; };
};

class ActHeal :public Action
{
public:
	ActHeal(int point) :Action::Action(point) {}

	void execute(Being *being)override;
	void printAct()override { cout << " heal " << this->point; };
};

class ActRest :public Action
{
public:
	//ActRest(int point) :Action::Action(point) {}

	void execute(Being *being)override;
};