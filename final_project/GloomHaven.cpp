#include "GloomHaven.h"

using namespace std;

bool minSortForActSp(act& a, act& b) {
	if (a.sp < b.sp) {
		return true;
	}
	else {
		return false;
	}
}

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

	for (int i = 0; i < charcterNum; i++) {

		// choose charcter by name
		string characterName;
		cin >> characterName;

		for (auto characterData : this->CharcterDatas) {
			// find character 
			if (characterName == characterData.name) {
				// choose skills
				int* skillsNum = new int[characterData.maxSkill];
				for (int i = 0; i < characterData.maxSkill; i++) {
					cin >> skillsNum[i];
				}

				Character newCharacter(characterData, skillsNum);
				this->Characters.push_back(newCharacter);
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
		if (level[this->Characters.size() - 2] == 0) {
			continue;
		}

		for (auto monsterData : this->MonsterDatas) {
			if (monsterData.name == name) {
				Monster monster;
				int hp, atk, range;
				if (level[this->Characters.size() - 2] == 1) {
					hp = monsterData.hp;
					atk = monsterData.atk;
					range = monsterData.range;
				}
				else {
					hp = monsterData.bossHp;
					atk = monsterData.bossAtk;
					range = monsterData.bossRange;
				}
				monster = Monster(hp, atk, range);
				monster.skills = monsterData.skills;
				monster.name = name;
				monster.pos = Position(posX, posY);

				this->Monsters.push_back(monster);
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
	for (auto& charcter : this->Characters) {
		while (true)
		{
			string choosePosition;
			cin >> choosePosition;

			Position intialPos = this->map.intialPositions[3];// weird----
			for (auto c : choosePosition) {
				intialPos = intialPos + Position::direction(c);
			}

			if (this->map.isIntialPos(intialPos)) {
				charcter.pos = intialPos;
				break;
			}
		}
	}
}

void GloomHaven::charactersTurn()
{
	size_t totalTurns = this->Characters.size();
	while (true)
	{
		break;
	}
}

void GloomHaven::monstersTurn()
{
	for (auto& monster : this->Monsters) {
		MonsterSkill skill = monster.skills[rand() % monster.skills.size()];
		act newAct;
		newAct.being = &monster;
		newAct.sp = skill.sp;
		for (auto& act : skill.act) {
			newAct.actions.push_back(act);
		}
		this->acts.push_back(newAct);
	}
}

void GloomHaven::execute()
{
	sort(this->acts.begin(), this->acts.end(), minSortForActSp);

	// one by one execute
	for (auto& act : this->acts) {
		for (auto& action : act.actions) {
			action->execute(act.being);
		}
	}
}

void GloomHaven::draw()
{
	char** drawBoard = new char* [this->map.width];
	for (int i = 0; i < this->map.width; i++) {
		drawBoard[i] = new char[this->map.height];
		for (int j = 0; j < this->map.height; j++)
		{
			drawBoard[i][j] = this->map.board[i][j];
		}
	}

	for (int i = 0; i < this->Characters.size(); i++) {
		drawBoard[this->Characters[i].pos.y][this->Characters[i].pos.x] = i + 'A';
	}

	for (int i = 0; i < this->Monsters.size(); i++) {
		drawBoard[this->Monsters[i].pos.y][this->Monsters[i].pos.x] = i + 'a';
	}

	for (int i = 0; i < this->map.width; i++) {
		for (int j = 0; j < this->map.height; j++)
		{
			cout << drawBoard[i][j];
		}
		cout << endl;
	}
	cout << endl;

}
