#include <iostream>
#include "Character.h"

Character::Character(CharcterData& cdata, int skillsNum[])
{
	this->name = cdata.name;
	this->hp = cdata.hp;
	this->maxHp = this->hp;
	this->sheldPoint = 0;

	for (int i = 0; i < cdata.maxSkill; i++) {
		this->skills.push_back(cdata.skills[skillsNum[i]]);
	}

}

void Character::move()
{
}

void Character::attack()
{
}

void Character::longRest()
{
}
