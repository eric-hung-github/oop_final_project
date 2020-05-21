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
public:
	vector<Action*>upAct;
	vector<Action*>downAct;


	CaracterSkill(string information);

};