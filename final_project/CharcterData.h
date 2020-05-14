#pragma once
#include "BeingData.h"
#include "CaracterSkill.h"

#include <vector>

using namespace std;

class CharcterData :public BeingData
{
	vector<CaracterSkill> skills;
	int maxCardsAmount;
};

