#include <iostream>
#include <fstream>
#include <sstream>

#include "GloomHaven.h"
#include "CaracterSkill.h"

using namespace std;

bool GloomHaven::loadCharcterData(string fileName)
{
	ifstream file = ifstream(fileName);
	if (!file.is_open()) {
		cout << "open file " << fileName << " error!" << endl;
		return false;
	}

	// reading n Charcter
	int CharcterDataCount = 0;
	file >> CharcterDataCount;

	for (int i = 0; i < CharcterDataCount; i++)
	{
		// new a CharcterData with name hp maxSkill
		stringstream basicInfor;
		string name ;
		int hp, maxSkill, allCapableSkills;

		file.ignore();
		file >> name;
		file >> hp >> maxSkill >> allCapableSkills;

		CharcterData aCharcterData(name, hp, maxSkill);
		//CharcterData aCharcterData;


		// reading skills into CharcterData's skill
		for (int j = 0; j < allCapableSkills; j++)
		{
			string skillInfor;
			getline(file, skillInfor);

			// enter a line of skill info to new a CaracterSkill 
			//and push into CharcterData's skill
			CaracterSkill aSkill = CaracterSkill(skillInfor);
			aCharcterData.skills.push_back(aSkill);
		}
	}

	file.close();
	return true;
}

bool GloomHaven::loadMonsterDatas(string fileName)
{
	return true;
}

void GloomHaven::chooseCharcters()
{
}

void GloomHaven::draw()
{
	for (int i = 0; i < this->map.width; i++) {
		for (int j = 0; j < this->map.height; j++)
		{
			cout << this->map.board[i][j];
		}
		cout << endl;
	}
}
