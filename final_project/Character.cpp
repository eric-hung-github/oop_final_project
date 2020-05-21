#include <iostream>
#include "Character.h"

Character::Character(CharcterData& cdata, int skillsNum[])
{
	this->hp = cdata.hp;

	for (int i = 0; i < sizeof(skillsNum) / sizeof(int); i++) {
		this->skills.push_back(cdata.skills[skillsNum[i]]);
	}

}
