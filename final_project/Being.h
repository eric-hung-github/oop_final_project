#pragma once
#include <string>

#include "Postition.h"
#include "Action.h"
#include "MapData.h"


using namespace std;

class Being
{
public:
	MapData *mapData;

	Position pos;
	string name;
	int hp,maxHp,sheldPoint;

	void heal(ActHeal);
	void sheild(ActSheild);
	virtual void move(ActMove);
	virtual void attack(ActAttack);
	virtual void longRest();
};