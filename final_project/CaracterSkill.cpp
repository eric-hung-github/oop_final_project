#include <string>
#include <sstream>

#include "CaracterSkill.h"
#include "Action.h"

CaracterSkill::CaracterSkill(string information)
{
	stringstream infor = stringstream(information);
	infor >> this->number;
	infor >> this->sp;

	ActAttack atk;
	this->upAct = atk;
}
