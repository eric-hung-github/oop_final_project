#include <sstream>

#include "MonsterSkill.h"

MonsterSkill::MonsterSkill(string information)
{
	// enter skill's number and speedPoint
	stringstream infor = stringstream(information);
	infor >> this->number;
	infor >> this->sp;

	enterAction(infor, this->act);
}

void enterAction(stringstream& infor, vector<Action*>& actions)
{
	string actType = "";
	int point = 0;
	if (!(infor >> actType)) {
		return;
	}


	Action* act;


	if (actType == "r") {

		return;
	}
	else if(actType == "d")
	{
		 
		return;
	}
	else if (actType == "attack") {
		infor >> point;

		string nextActType, tempLine;
		int nextPoint = 0;
		infor >> nextActType;

		// is enter rangeer attack
		if (nextActType == "range") {
			infor >> nextPoint;
			act = new ActAttack(point, nextPoint);
		}
		else {
			act = new ActAttack(point, 0);

			// add back string 
			string temp;
			getline(infor, temp);
			temp = nextActType + temp;
			infor = stringstream(temp);
		}

	}
	else if (actType == "heal") {
		infor >> point;
		act = new ActHeal(point);
	}
	else if (actType == "shield") {
		infor >> point;
		act = new ActSheild(point);
	}
	else if (actType == "move") {
		infor >> point;
		act = new ActMove(point);
	}

	actions.push_back(act);
	enterAction(infor, actions);
}