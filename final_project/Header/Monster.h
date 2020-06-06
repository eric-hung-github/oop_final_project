#pragma once
#include <vector>
#include "Postition.h"
#include "MonsterSkill.h"
#include "Being.h"

using namespace std;

class Monster :public Being
{

public:
	int atk, range;
	vector<MonsterSkill> skills;
	Postition pos;

	Monster();
	Monster(int hp, int atk, int range);
};

