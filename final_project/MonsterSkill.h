#pragma once
#include <sstream>

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

