#include <iostream>
#include "Character.h"

Character::Character(CharcterData cdata, int skillsNum[])
{
	this->hp = cdata.hp;
	this->atk = cdata.atk;
	this->def = cdata.def;
	this->sheild = cdata.sheild;

	cout<< sizeof skillsNum / sizeof(int);

	for (int i = 0; i < sizeof skillsNum / sizeof (int); i++) {
		
	}

}
