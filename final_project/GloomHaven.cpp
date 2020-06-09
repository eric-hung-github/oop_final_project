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
				newCharacter.mapData = &this->map;
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
		if (level[this->Characters.size() - 2] == 0) {
			continue;
		}


		for (auto monsterData : this->MonsterDatas) {
			if (monsterData.name == name) {
				Monster newMonster;
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
				newMonster = Monster(hp, atk, range);
				newMonster.skills = monsterData.skills;
				newMonster.equipedSkills = newMonster.skills;
				newMonster.name = name;
				newMonster.pos = Position(posX, posY);
				newMonster.mapData = &this->map;

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
	for (auto& charcter : this->Characters) {
		while (true)
		{
			string choosePosition;
			cin >> choosePosition;

			Position intialPos = *(this->map.intialPositions.end() - 1);// weird----
			for (auto c : choosePosition) {
				if (c == 'e')continue;
				intialPos = intialPos + Position::direction(c);
			}

			if (this->map.isIntialPos(intialPos)) {
				charcter.second.pos = intialPos;
				this->map.updateVisiblePosition(intialPos);
				break;
			}
		}
	}

}

void GloomHaven::charactersTurn()
{
	//std::map<char, int[]>playedCard;

	size_t totalTurns = this->Characters.size();

	int** characterPlayCard = new int*[this->Characters.size()];

	while (totalTurns > 0) {
		char characterIndex;
		string command;
		cin >> characterIndex >> command;

		if (command == "-1")// long rest
		{
			if (this->Characters[characterIndex].playedSkill.size() < 2) {

				break;
			}
			else {
				act newAct;
				newAct.actions[0] = new ActRest;
				newAct.sp = 99;
				newAct.being = &this->Characters[characterIndex];

				this->acts.push_back(newAct);

				totalTurns -= 1;
			}

		}
		else if (command == "check")// check
		{
			// cout card
			cout << "hand: ";
			for (auto hasSkill : this->Characters[characterIndex].skills) {
				cout << hasSkill.first << ' ';
			}
			cout << "; discard: ";
			for (auto playedSkill : this->Characters[characterIndex].playedSkill) {
				cout << playedSkill.first << ' ';
			}
			cout << endl;
		}
		else // play card
		{
			int playedSkill[2];
			playedSkill[0] = stoi(command);
			cin >> command;
			playedSkill[1] = stoi(command);

			characterPlayCard[characterIndex - 'A'] = playedSkill;
		}
	}

	char chosecard[4][3] = { 0 };

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cin >> chosecard[i][j];
		}
	}
	for (auto& character : this->Characters)
	{
		int i = 0;
		string merge;
		cin >> merge;
		act newAct;
		newAct.being = &character.second;
		if (character.second.skills[chosecard[i][1]].sp >
			character.second.skills[chosecard[i][2]].sp)
			newAct.sp = character.second.skills[chosecard[i][2]].sp;
		else
			newAct.sp = character.second.skills[chosecard[i][1]].sp;

		if (merge[0] == chosecard[i][1]) {
			if (merge[1] == 'u')
			{
				//newAct.actions.push_back(character.second.skills[(int)chosecard[i][1]].upAct);
				//newAct.actions.push_back(character.second.skills[(int)chosecard[i][2]].downAct);
			}
			else if (merge[1] == 'd')
			{
				//newAct.actions.push_back(character.second.skills[(int)chosecard[i][1]].downAct);
				//newAct.actions.push_back(character.second.skills[(int)chosecard[i][2]].upAct);
			}
		}
		else if (merge[1] == chosecard[i][2])
		{
			if (merge[1] == 'u')
			{
				//newAct.actions.push_back(character.second.skills[(int)chosecard[i][2]].upAct);
				//newAct.actions.push_back(character.second.skills[(int)chosecard[i][1]].downAct);
			}
			else if (merge[1] == 'd')
			{
				//newAct.actions.push_back(character.second.skills[(int)chosecard[i][2]].downAct);
				//newAct.actions.push_back(character.second.skills[(int)chosecard[i][1]].upAct);
			}
		}
		i++;
	}

}

void GloomHaven::monstersTurn()
{
	for (auto& monster : this->Monsters) {
		// is valid
		if (map.visiblePosition.find(monster.second.pos) == map.visiblePosition.end()) {
			continue;
		}
		// is Alive
		if (monster.second.hp <= 0)continue;

		int skillIndex = rand() % monster.second.skills.size();
		MonsterSkill skill = monster.second.skills[skillIndex];
		monster.second.skills.erase(monster.second.skills.begin() + skillIndex);

		if (skill.redraw)monster.second.skills = monster.second.equipedSkills;

		act newAct;
		newAct.being = &(monster.second);
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
		this->updateGame();
		this->draw();
	}
}

void GloomHaven::updateGame()
{
	for (auto character : this->Characters) {
		map.updateVisiblePosition(character.second.pos);
	}

}

void GloomHaven::draw()
{
	char** drawBoard = new char* [this->map.height];
	for (int i = 0; i < this->map.height; i++) {
		drawBoard[i] = new char[this->map.width];
		for (int j = 0; j < this->map.width; j++)
		{
			Position pos = Position(j, i);
			if (map.visiblePosition.find({ j,i }) != map.visiblePosition.end()) {
				drawBoard[i][j] = map.board[i][j];
			}
			else {
				drawBoard[i][j] = ' ';
			}
		}
	}

	for (auto character : this->Characters) {
		drawBoard[character.second.pos.y][character.second.pos.x] = character.first;
	}

	for (auto monster : this->Monsters) {
		if (this->map.visiblePosition.find(monster.second.pos) == this->map.visiblePosition.end()) {
			continue;
		}
		drawBoard[monster.second.pos.y][monster.second.pos.x] = monster.first;
	}

	for (int i = 0; i < this->map.height; i++) {
		for (int j = 0; j < this->map.width; j++)
		{
			cout << drawBoard[i][j];
		}
		cout << endl;
	}
	cout << endl;

}
