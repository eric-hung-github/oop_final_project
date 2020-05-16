#pragma once
#include <string>
#include <vector>
#include "Skill.h"
#include "Action.h"

using namespace std;

// use recursive to enter skills
void enterAction(stringstream &infor, vector<Action*> &actions);

class CaracterSkill :public Skill
{
	vector<Action*>upAct;
	vector<Action*>downAct;

public:
	CaracterSkill(string information);

};