#pragma once
#include <string>

#include "Postition.h"
#include "Action.h"


using namespace std;

class GloomHaven;

class Being
{
public:
	GloomHaven *gameData;

	Position pos;
	string name;
	int hp,maxHp,sheldPoint;

	void heal(ActHeal);
	void sheild(ActSheild);
	virtual void move(ActMove);
	virtual void attack(ActAttack);
	virtual void longRest();
};