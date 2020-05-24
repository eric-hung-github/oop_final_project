#pragma once
#include "Skill.h"
#include "Action.h"

using namespace std;

class MonsterSkill :public Skill
{
public:
	vector<Action*> act;
	bool redraw;

	MonsterSkill(string infor);
	void printSkill();
};

