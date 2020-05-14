#pragma once

#include <vector>
#include <string>

#include "BeingData.h"
#include "CaracterSkill.h"

using namespace std;

class CharcterData :public BeingData
{
public:

	vector<CaracterSkill> skills;
	int maxSkill;

	CharcterData(string name, int hp, int maxSkill);

};

