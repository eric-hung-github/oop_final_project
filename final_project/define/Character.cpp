#include <iostream>
#include "Character.h"

Character::Character(CharcterData& cdata, int skillsNum[])
{
	this->name = cdata.name;
	this->hp = cdata.hp;

	for (int i = 0; i < cdata.maxSkill; i++) {
		this->skills.push_back(cdata.skills[skillsNum[i]]);
	}

}
