#include <sstream>

#include "MonsterSkill.h"

bool enterAction(stringstream& infor, vector<Action*>& actions);

MonsterSkill::MonsterSkill(string information)
{
	// enter skill's number and speedPoint
	stringstream infor = stringstream(information);
	string emptyName;
	infor >> emptyName;
	infor >> this->number;
	infor >> this->sp;

	this->redraw = enterAction(infor, this->act);
}

void MonsterSkill::printSkill()
{
	cout << this->number << " " << this->sp;
	for (auto act : this->act) {
		act->printAct();
	}

	cout << endl;
}

bool enterAction(stringstream& infor, vector<Action*>& actions)
{
	string actType = "";
	int point = 0;
	if (!(infor >> actType)) {
		return false;
	}


	Action* act;


	if (actType == "r") {
		return true;
	}
	else if (actType == "d")
	{
		return false;
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
		//infor >> point;
		string steps;
		infor >> steps;
		act = new ActMove(0,steps);
	}

	actions.push_back(act);
	enterAction(infor, actions);
}