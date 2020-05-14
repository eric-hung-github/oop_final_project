#pragma once
#include "Skill.h"
#include "Action.h"

using namespace std;

class CaracterSkill :public Skill
{
	Action upAct;
	Action downAct;
};