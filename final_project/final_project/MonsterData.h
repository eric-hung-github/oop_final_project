#pragma once
#include <vector>
#include "BeingData.h"
#include "MonsterSkill.h"

using namespace std;

class MonsterData :public BeingData
{
public:
	vector< MonsterSkill> skills;
	int atk, range;
	int bossHp, bossAtk, bossRange;

	MonsterData(string name, int data[])
	{
		this->name = name;
		this->hp = data[0];
		this->atk = data[1];
		this->range = data[2];
		this->bossHp = data[3];
		this->bossAtk = data[4];
		this->bossRange = data[5];
	}

};

