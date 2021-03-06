#include <iostream>
#include "Character.h"
#include "GloomHaven.h"

Character::Character()
{

}

Character::Character(CharcterData& cdata, int skillsNum[])
{
	this->name = cdata.name;
	this->hp = cdata.hp;
	this->maxHp = this->hp;
	this->sheldPoint = 0;

	for (int i = 0; i < cdata.maxSkill; i++)
	{
		this->skills.insert({ skillsNum[i],cdata.skills[skillsNum[i]] });
	}

}

void Character::move(ActMove action)
{
	string steps;


	while (cin >> steps)
	{
		if (steps.size() > action.point)
		{
			cout << "ERROR MOVE! you can't move so far " << endl;
			continue;
		}

		Position nextPos = this->pos;

		bool validMove = true;
		for (auto step : steps)
		{
			if (this->gameData->isCharacterMoveable(this, nextPos + Position::direction(step)))
			{
				nextPos = nextPos + Position::direction(step);
			}
			else
			{
				cout << "Invalid Move" << endl;
				validMove = false;
			}
		}
		if (validMove)
		{
			this->pos = nextPos;
			break;
		}

	}
}

void Character::attack(ActAttack action)
{
	char targetIndex;

	while (cin >> targetIndex)
	{
		if (targetIndex == '0')return;
		Monster* targetMonster = &this->gameData->Monsters[targetIndex];
		if (this->gameData->lockMonster(this->pos, action.range, targetMonster))
		{
			targetMonster->hurt(action.point);
			break;
		}

	}

}

void Character::hurt(int damage)
{
	cout << this->name << "was hurt " << damage << endl;
	if (damage - this->sheldPoint < 0)
	{
		this->sheldPoint -= damage;
	}
	else
	{
		this->hp -= (damage - this->sheldPoint);
	}
}

void Character::longRest()
{
	int index;
	cout << "pleas discard";
	for (auto skill : this->playedSkill)
	{
		cout << ' ' << skill.first;
	}
	cout << endl;
	cin >> index;
	this->playedSkill.erase(index);
	for (auto skill : this->playedSkill)
	{
		this->skills.insert(skill);
	}
	this->playedSkill.clear();
	this->heal(ActRest::restHeal);
	cout << "succees discard and heal 2 hp" << endl;
}
