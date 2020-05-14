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
};

class ActSheild :public Action
{

};

class ActMove :public Action
{

};

class ActHeal :public Action
{

};

class ActRest :public Action
{

};