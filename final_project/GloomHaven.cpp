#include "GloomHaven.h"

using namespace std;

/*
bool minSortForActSp(act& a, act& b)
{
	if (a.sp < b.sp)
	{
		return true;
	}
	else if (a.sp = b.sp)
	{
		if ((typeid(&a.being) == typeid(Character)) && (typeid(&b.being) == typeid(Character)))
		{
			if (a.spTwo == b.spTwo)return a.being->name < b.being->name;
			else return a.spTwo < b.spTwo;
		}

		if ((typeid(&a.being) == typeid(Character)) && (typeid(&b.being) == typeid(Monster)))
		{
			return true;
		}

		if ((typeid(&a.being) == typeid(Monster)) && (typeid(&b.being) == typeid(Character)))
		{
			return false;
		}

		if ((typeid(&a.being) == typeid(Monster)) && (typeid(&b.being) == typeid(Monster)))
		{
			return a.being->name < b.being->name;
		}
	}
	else
	{
		return false;
	}
}

*/

bool GloomHaven::loadCharcterData(string fileName)
{
	ifstream file(fileName);
	if (!file.is_open())
	{
		cout << "open file " << fileName << " error!" << endl;
		return false;
	}

	// reading n Charcter
	int CharcterDataCount = 0;
	file >> CharcterDataCount;

	for (int i = 0; i < CharcterDataCount; i++)
	{
		// new a CharcterData with name hp maxSkill
		string name = "";
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
		this->CharcterDatas.push_back(aCharcterData);
	}

	file.close();

	/*----teset------
	for (auto charcterData : this->CharcterDatas) {
		cout << charcterData.name << endl;
		for (auto skill : charcterData.skills) {
			skill.printSkill();
		}
	}
	*/

	return true;
}

bool GloomHaven::loadMonsterDatas(string fileName)
{
	ifstream file;
	file.open(fileName);
	if (!file.is_open())
	{
		cout << "Open file error." << endl;
		return false;
	}


	int MonsterDataCount;
	file >> MonsterDataCount;
	for (int i = 0; i < MonsterDataCount; i++)
	{
		string name;
		int data[6] = { 0 };
		file >> name;
		for (int i = 0; i < 6; i++)
		{
			file >> data[i];
		}
		file.ignore();

		MonsterData aMonsterdata(name, data);

		for (int j = 0; j < 6; j++)
		{
			string skillInfor;
			getline(file, skillInfor);


			MonsterSkill aSkill = MonsterSkill(skillInfor);
			aMonsterdata.skills.push_back(aSkill);
		}

		this->MonsterDatas.push_back(aMonsterdata);
	}

	/*----teset------
	for (auto charcterData : this->CharcterDatas) {
		cout << charcterData.name << endl;
		for (auto skill : charcterData.skills) {
			skill.printSkill();
		}
	}
	*/

	return true;
}

bool GloomHaven::loadMapData(string fileName)
{
	return this->map.load(fileName);
}

void GloomHaven::chooseCharcters()
{
	int charcterNum = 0;
	cin >> charcterNum;

	for (int i = 0; i < charcterNum; i++)
	{

		// choose charcter by name
		string characterName;
		cin >> characterName;

		for (auto characterData : this->CharcterDatas)
		{
			// find character 
			if (characterName == characterData.name)
			{
				// choose skills
				int* skillsNum = new int[characterData.maxSkill];
				for (int i = 0; i < characterData.maxSkill; i++)
				{
					cin >> skillsNum[i];
				}

				Character newCharacter(characterData, skillsNum);
				newCharacter.gameData = this;
				this->Characters.insert({ i + 'A',newCharacter });
				break;
			}
		}
	}

	/*
		for (auto charcter : this->Characters) {
		cout << charcter.name << endl;
		for (auto skill : charcter.skills) {
			skill.printSkill();
		}
	}
	*/

}

void GloomHaven::generateMonster()
{
	int monsterCount = 0;
	for (int i = 0; i < this->map.monsterGenerInfor.size(); i++)
	{
		// reading generateInformation
		stringstream generateInfor(this->map.monsterGenerInfor[i]);
		string	name;
		int posX, posY, level[3];

		// 
		generateInfor >> name >> posX >> posY;
		for (int i = 0; i < 3; i++)
		{
			generateInfor >> level[i];
		}

		// if no nedd to generate
		if (level[this->Characters.size() - 2] == 0)
		{
			continue;
		}


		for (auto monsterData : this->MonsterDatas)
		{
			if (monsterData.name == name)
			{
				Monster newMonster;
				int hp, atk, range;
				if (level[this->Characters.size() - 2] == 1)
				{
					hp = monsterData.hp;
					atk = monsterData.atk;
					range = monsterData.range;
				}
				else
				{
					hp = monsterData.bossHp;
					atk = monsterData.bossAtk;
					range = monsterData.bossRange;
				}
				newMonster = Monster(hp, atk, range);
				newMonster.skills = monsterData.skills;
				newMonster.equipedSkills = newMonster.skills;
				newMonster.name = name;
				newMonster.pos = Position(posX, posY);
				newMonster.gameData = this;

				this->Monsters.insert({ monsterCount + 'a',newMonster });
				monsterCount++;
			}

		}

	}

	/*
		for (auto monster : this->Monsters) {
		cout << monster.name << endl;
		for (auto skill : monster.skills) {
			skill.printSkill();
		}
	}
	*/


}

void GloomHaven::chooseIntialPos()
{
	for (auto& charcter : this->Characters)
	{
		while (true)
		{
			string choosePosition;
			cin >> choosePosition;

			Position intialPos = (this->map.intialPositions[0]);// weird----
			for (auto intialPosition : this->map.intialPositions)
			{
				if (intialPosition.x + intialPosition.y < intialPos.x + intialPos.y)
				{
					intialPos = intialPosition;
				}
				else if (intialPosition.x + intialPosition.y == intialPos.x + intialPos.y)
				{
					if (intialPosition.y < intialPos.y)
					{
						intialPos = intialPosition;
					}

				}
			}


			for (auto c : choosePosition)
			{
				if (c == 'e')continue;
				intialPos = intialPos + Position::direction(c);
			}

			if (this->map.isIntialPos(intialPos))
			{
				charcter.second.pos = intialPos;
				this->map.updateVisiblePosition(intialPos);
				break;
			}
		}
	}

}

void GloomHaven::charactersTurn()
{
	cin.ignore();

	size_t totalTurns = this->Characters.size();

	char chararcterIndex;
	string inputCommand;
	while (totalTurns>0)
	{
		getline(cin, inputCommand);

		stringstream ss(inputCommand);
		ss >> chararcterIndex;
		ss >> inputCommand;

		if (inputCommand == "check")
		{
			// cout card
			cout << "hand: ";
			for (auto hasSkill : this->Characters[chararcterIndex].skills)
			{
				cout << hasSkill.first << ' ';
			}
			cout << "; discard: ";
			for (auto playedSkill : this->Characters[chararcterIndex].playedSkill)
			{
				cout << playedSkill.first << ' ';
			}
			cout << endl;

			continue;
		}
		else if (inputCommand == "-1")
		{
			if (characterChooseCards.find(chararcterIndex) != characterChooseCards.end())
			{
				cout << "You have played Card!!!" << endl;

			}
			else
			{
				characterChooseCards.insert(make_pair(chararcterIndex,make_pair(CaracterSkill::longRest, CaracterSkill::longRest)));
				totalTurns -= 1;
			}

		}
		else
		{
			if (characterChooseCards.find(chararcterIndex) != characterChooseCards.end())
			{
				cout << "You have played Card!!!" << endl;
			}
			else
			{
				int cards[2];
				cards[0] = stoi(inputCommand);
				ss >> cards[1];
				auto skillOne = this->Characters[chararcterIndex].skills[cards[0]];
				auto skillTwo = this->Characters[chararcterIndex].skills[cards[1]];
				characterChooseCards.insert(make_pair(chararcterIndex, std::make_pair(skillOne,skillTwo)));
				totalTurns -= 1;
			}

		}
	}

}

void GloomHaven::monsterPlayCard(pair<char, MonsterSkill>)
{
}

void GloomHaven::monstersTurn()
{
	for (auto& monster : this->Monsters)
	{
		// is valid
		if (map.visiblePosition.find(monster.second.pos) == map.visiblePosition.end())
		{
			continue;
		}
		// is Alive
		if (monster.second.hp <= 0)continue;

		int skillIndex = rand() % monster.second.skills.size();
		MonsterSkill skill = monster.second.skills[skillIndex];
		monster.second.skills.erase(monster.second.skills.begin() + skillIndex);

		if (skill.redraw)monster.second.skills = monster.second.equipedSkills;

		this->monsterChooseCards.insert({ monster.first, skill });
	}
}

void GloomHaven::characterPlayCard(pair<char, pair<CaracterSkill, CaracterSkill>> cards)
{
	auto character = *this->Characters.find(cards.first);

	int i = 0;
	string inputCommand;
	CaracterSkill newskill1 = character.second.skills[chosecards[character.first].first];
	CaracterSkill newskill2 = character.second.skills[chosecards[character.first].second];
	newAct.being = &character.second;
	if (character.second.skills[chosecards[character.first].first].sp >
		character.second.skills[chosecards[character.first].second].sp)
	{
		newAct.sp = character.second.skills[chosecards[character.first].second].sp;
		newAct.spTwo = character.second.skills[chosecards[character.first].first].sp;
	}
	else
	{
		newAct.sp = character.second.skills[chosecards[character.first].first].sp;
		newAct.spTwo = character.second.skills[chosecards[character.first].second].sp;
	}

	if (inputCommand[0] == chosecards[character.first].first)
	{
		if (inputCommand[1] == 'u')
		{
			newAct.actions.push_back(newskill1.upAct[chosecards[character.first].first]);
			newAct.actions.push_back(newskill2.downAct[chosecards[character.first].second]);
		}
		else if (inputCommand[1] == 'd')
		{
			newAct.actions.push_back(newskill1.downAct[chosecards[character.first].first]);
			newAct.actions.push_back(newskill2.upAct[chosecards[character.first].second]);
		}
	}
	else if (inputCommand[1] == chosecards[character.first].second)
	{
		if (inputCommand[1] == 'u')
		{
			newAct.actions.push_back(newskill2.upAct[chosecards[character.first].second]);
			newAct.actions.push_back(newskill1.downAct[chosecards[character.first].first]);
		}
		else if (inputCommand[1] == 'd')
		{
			newAct.actions.push_back(newskill2.downAct[chosecards[character.first].second]);
			newAct.actions.push_back(newskill1.upAct[chosecards[character.first].first]);
		}
	}
	this->acts.push_back(newAct);
}

void GloomHaven::startTurn()
{
}

bool GloomHaven::isPositionConflict(Being* being, Position pos)
{
	for (auto character : this->Characters)
	{
		if (&character.second != being && character.second.pos == pos)return true;
	}

	for (auto monster : this->Monsters)
	{
		if (&monster.second != being && monster.second.pos == pos)return true;
	}
	return false;
}

bool GloomHaven::isCharacterMoveable(Being* being, Position pos)
{
	if (this->map.board[pos.y][pos.x] != this->map.block && !isPositionConflict(being, pos))return true;
	return false;
}

bool GloomHaven::isMonsterMoveable(Being* being, Position pos)
{
	if (this->map.board[pos.y][pos.x] == this->map.space && !isPositionConflict(being, pos))return true;
	return false;
}

bool GloomHaven::isAttackable(Position sub, Position target, int range)
{
	return false;
}

bool GloomHaven::lockCharacter(Position pos, int Range, Character* character)
{
	return false;
}

bool GloomHaven::lockMonster(Position pos, int Range, Monster* monster)
{
	return false;
}

void GloomHaven::updateGame()
{
	for (auto character : this->Characters)
	{
		map.updateVisiblePosition(character.second.pos);
	}

}

void GloomHaven::draw()
{
	char** drawBoard = new char* [this->map.height];
	for (int i = 0; i < this->map.height; i++)
	{
		drawBoard[i] = new char[this->map.width];
		for (int j = 0; j < this->map.width; j++)
		{
			Position pos = Position(j, i);
			if (map.visiblePosition.find({ j,i }) != map.visiblePosition.end())
			{
				drawBoard[i][j] = map.board[i][j];
			}
			else
			{
				drawBoard[i][j] = ' ';
			}
		}
	}

	for (auto character : this->Characters)
	{
		drawBoard[character.second.pos.y][character.second.pos.x] = character.first;
	}

	for (auto monster : this->Monsters)
	{
		if (this->map.visiblePosition.find(monster.second.pos) == this->map.visiblePosition.end())
		{
			continue;
		}
		drawBoard[monster.second.pos.y][monster.second.pos.x] = monster.first;
	}

	for (int i = 0; i < this->map.height; i++)
	{
		for (int j = 0; j < this->map.width; j++)
		{
			cout << drawBoard[i][j];
		}
		cout << endl;
	}
	cout << endl;

}