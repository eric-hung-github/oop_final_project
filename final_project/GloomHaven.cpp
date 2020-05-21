#include <iostream>
#include <fstream>

#include "GloomHaven.h"
#include "CharcterData.h"
#include "CaracterSkill.h"

using namespace std;

bool GloomHaven::loadCharcterData(string fileName)
{
	ifstream file(fileName);
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
		string name="";
		int hp, maxSkill, allCapableSkills;

		file >> name;
		file >> hp >> maxSkill >> allCapableSkills;
		file.ignore();

		CharcterData aCharcterData(name, hp, maxSkill);

		// reading skills into CharcterData's skill
		for (int j = 0; j < allCapableSkills; j++)
		{
			string skillInfor;
			getline(file, skillInfor);

			// enter a line of skill info to new a CaracterSkill 
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
	int charcterNum = 0;
	cin >> charcterNum;

	for (int i = 0; i < charcterNum; i++) {

		// choose charcter by name
		string characterName;
		cin >> characterName;

		
		for (auto character : this->CharcterDatas) {
			// find character 
			if (characterName == character.name) {
				// choose skills
				int *skillsNum=new int[character.maxSkill];
				for (int i = 0; i < character.maxSkill; i++) {
					cin >> skillsNum[i];
				}

				Character newCharacter(character,skillsNum);
				this->Characters.push_back(newCharacter);
			}
		}
	}
}

void GloomHaven::generateMonster()
{

}

void GloomHaven::chooseIntialPos()
{
}

void GloomHaven::charactersTurn()
{
}

void GloomHaven::monstersTurn()
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
