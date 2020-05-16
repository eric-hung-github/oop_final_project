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

	string actType;
	int point;
	// fill Action into upAct
	while (infor>> actType>> point)
	{
		Action* act = nullptr;;

		if (actType == "-") {
			break;
		}else if (actType == "move") {
			//*act = ActAttack::ActAttack(point);
		}
		else if (actType == "move") {

		}
		else if (actType == "move") {

		}
		else if (actType == "move") {

		}
	}

	while (infor >> actType)
	{
		Action* act = nullptr;;

		if (actType == "-") {
			break;
		}
		else if (actType == "move") {
			//*act = ActAttack::ActAttack(point);
		}
		else if (actType == "move") {

		}
		else if (actType == "move") {

		}
		else if (actType == "move") {

		}
	}
}

