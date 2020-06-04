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
	this->equipedSkills = this->skills;
}

void Character::move(Action *action)
{
}

void Character::attack(Action *action)
{
}

void Character::longRest()
{
}
