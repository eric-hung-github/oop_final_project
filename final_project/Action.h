#pragma once
#include "Being.h"

class Action
{
public:
	int point;
	virtual void execute(Being being);
};

class ActAttack :public Action
{
	//  charcter
	void execute (Being being);
};

class ActSheild :public Action
{
	void execute(Being being);
};

class ActMove :public Action
{
	void execute(Being being);
};

class ActHeal :public Action
{
	void execute(Being being);
};

class ActRest :public Action
{
	void execute(Being being);
};