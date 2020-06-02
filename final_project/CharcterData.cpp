#include "CharcterData.h"

using namespace std;

CharcterData::CharcterData()
{
	this->name = "";
	this->hp = 0;
	this->maxSkill = 0;
}

CharcterData::CharcterData(string name, int hp, int maxSkill)
{
	this->name = name;
	this->hp = hp;
	this->maxSkill = maxSkill;
}
