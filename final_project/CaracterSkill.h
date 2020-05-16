#pragma once
#include <string>
#include <vector>
#include "Skill.h"
#include "Action.h"

using namespace std;

//vector<Action*> enterAction(stringstream infor);

class CaracterSkill :public Skill
{
	vector<Action*>upAct;
	vector<Action*>downAct;

public:
	CaracterSkill(string information);

};