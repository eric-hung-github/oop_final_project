#include <string>
#include <sstream>

#include "CaracterSkill.h"
#include "Action.h"


CaracterSkill::CaracterSkill(string information)
{
	// enter skill's number and speedPoint
	stringstream infor = stringstream(information);
	infor >> this->number;
	infor >> this->sp;

	enterAction(infor, this->upAct);
	enterAction(infor, this->downAct);
}

void enterAction(stringstream& infor, vector<Action*>& actions)
{
	string actType = "";
	int point = 0;
	if (!(infor >> actType >> point)) {
		return;
	}


	Action* act = nullptr;


	if (actType == "-") {
		return;
	}
	else if (actType == "attack") {

		string nextActType, tempLine;
		int nextPoint;
		infor >> nextActType >> nextPoint;

		// is enter rangeer attack
		if (nextActType == "range") {

			act = &ActAttack::ActAttack(point, nextPoint);
		}
		else {
			act = &ActAttack::ActAttack(point, 0);

			// add back string 

		}

	}
	else if (actType == "heal") {
		act = &ActHeal::ActHeal(point);
	}
	else if (actType == "shield") {
		act = &ActSheild::ActSheild(point);
	}
	else if (actType == "move") {
		act = &ActMove::ActMove(point);
	}

	actions.push_back(act);
	enterAction(infor, actions);
}
