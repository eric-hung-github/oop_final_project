#include "CaracterSkill.h"

using namespace std;

bool enterCharcterAct(stringstream& infor, vector<Action*>& actions)
{
	string actType = "";
	int point = 0;
	if (!(infor >> actType)) {
		return false;
	}


	Action* act;


	if (actType == "-") {

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
		infor >> point;
		act = new ActMove(point);
	}

	actions.push_back(act);
	enterCharcterAct(infor, actions);

	return true;
}

CaracterSkill::CaracterSkill(string information)
{
	// enter skill's number and speedPoint
	stringstream infor = stringstream(information);
	infor >> this->number;
	infor >> this->sp;

	enterCharcterAct(infor, this->upAct);
	enterCharcterAct(infor, this->downAct);
}


CaracterSkill::CaracterSkill(CaracterSkill const& input)
{
    this->upAct=input.upAct;
    this->downAct=input.downAct;
}

void CaracterSkill::printSkill()
{
	cout << this->number << " " << this->sp;

	for (auto act : this->upAct) {
		act->printAct();
	}

	for (auto act : this->downAct) {
		act->printAct();
	}

	cout << endl;
}




