#pragma once
//#include <vector>
#include "BeingData.h"
#include "MonsterSkill.h"

using namespace std;

class MonsterData :public BeingData
{
public:
	vector< MonsterSkill> skills;
	int atk, range;
	int bossHp, bossAtk, bossRange;



};

