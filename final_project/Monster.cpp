#include "Monster.h"
#include "GloomHaven.h"

Monster::Monster()
{
	this->hp = 0;
	this->maxHp = this->hp;
	this->atk = 0;
	this->range = 0;
	this->sheldPoint = 0;
}

Monster::Monster(int hp, int atk, int range)
{
	this->hp = hp;
	this->maxHp = this->hp;
	this->atk = atk;
	this->range = range;
	this->sheldPoint = 0;
}

void Monster::move(ActMove action)
{
	for (auto step : action.steps)
	{
		if (this->gameData->isMonsterMoveable(this, this->pos + Position::direction(step)))
		{

			this->pos = this->pos + Position::direction(step);

		}
		else
		{
			break;
		}
	}
}

void Monster::attack(ActAttack action)
{
	Character* targetCharacter = new Character;
	if (this->gameData->lockCharacter(this->pos, action.range, targetCharacter))
	{
		targetCharacter->hurt(action.point);
	}
	else
	{
		return;
	}
}

void Monster::hurt(int damage)
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
