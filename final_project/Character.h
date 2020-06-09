#pragma once

#include "Being.h"
#include "CharcterData.h"
#include "CaracterSkill.h"
#include <vector>
#include <map>

using namespace std;

class Character :public Being
{
public:

	map<int,CaracterSkill> playedSkill;
	map<int,CaracterSkill> skills;

	Character();
	Character(CharcterData &cdata,int skillsNum[]);

	void move(ActMove action)override;
	void attack(ActAttack action)override;
	void longRest()override;
};

