#include <fstream>
#include <iostream>

#include "CharcterData.h"

using namespace std;

CharcterData::CharcterData()
{
	this->name = "";
	this->health = 0;
	this->maxSkill = 0;
}

CharcterData::CharcterData(string name, int hp, int maxSkill)
{
	this->name = name;
	this->health = hp;
	this->maxSkill = maxSkill;
}
