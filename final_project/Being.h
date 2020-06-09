#pragma once
#include <string>

#include "Postition.h"
#include "Action.h"


using namespace std;

class Being
{
public:
	Position pos;
	string name;
	int hp,maxHp,sheldPoint;

	void heal(Action *action);
	void sheild(Action *action);
	virtual void move(Action *action);
	virtual void attack(Action *action);
	virtual void longRest();
};