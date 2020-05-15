#include <iostream>
#include <fstream>

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

	int CharcterDataCount = 0;
	file >> CharcterDataCount;

	for (int  i = 0; i < CharcterDataCount; i++)
	{
		string name;
		int hp, maxSkill,allCapableSkills;

		file >> name;
		file >> hp >> maxSkill >> allCapableSkills;

		CharcterData aCharcterData(name,hp,maxSkill);

		for (int j = 0; j < allCapableSkills; j++)
		{
			string skillInfor;
			getline(file, skillInfor);
			
			CaracterSkill aSkill = CaracterSkill(skillInfor);
			aCharcterData.skills.push_back(aSkill);
		}
	}
	
	

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
			cout<<this->map.board[i][j];
		}
		cout << endl;
	}
}
