#include <fstream>
#include <iostream>

#include "CharcterData.h"

using namespace std;

CharcterData::CharcterData(string name, int hp, int maxSkill)
{
	this->name = name;
	this->health = hp;
	this->maxSkill = maxSkill;
}
