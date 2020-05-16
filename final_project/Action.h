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
public:
	int range;
	//  
	void execute (Being being)override;
};

class ActSheild :public Action
{
public:
	void execute(Being being)override;
};

class ActMove :public Action
{
public:
	vector<Postition> direction;
	void execute(Being being)override;
};

class ActHeal :public Action
{
public:
	void execute(Being being)override;
};

class ActRest :public Action
{
public:
	void execute(Being being)override;
};