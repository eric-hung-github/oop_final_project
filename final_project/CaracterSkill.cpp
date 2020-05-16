#include <string>
#include <sstream>

#include "CaracterSkill.h"
#include "Action.h"

vector<Action*> enterAction(stringstream infor) {

}

CaracterSkill::CaracterSkill(string information)
{
	// enter skill's number and speedPoint
	stringstream infor = stringstream(information);
	infor >> this->number;
	infor >> this->sp;


}

