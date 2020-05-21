#pragma once

#include "Being.h"
#include "CharcterData.h"
#include "CaracterSkill.h"
#include <vector>

using namespace std;

class Character :public Being
{
public:
	vector<CaracterSkill> skills;

	Character(CharcterData &cdata,int skillsNum[]);

	void move();
	void attack();
	void heal();
	void shield();
};

