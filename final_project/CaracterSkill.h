#pragma once
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include "Skill.h"
#include "Action.h"

using namespace std;
// use recursive to enter skills
void enterMonsterAct(stringstream &infor, vector<Action*> &actions);

class CaracterSkill :public Skill
{
public:
	vector<Action*>upAct;
	vector<Action*>downAct;

	CaracterSkill(string information);

	void printSkill();
};