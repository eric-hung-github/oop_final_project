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
	cout << "Please enter the number of characters (2~4): ";
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
				this->Characters.insert({i+'A',newCharacter});
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

		int monsterCount = 0;
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
				newMonster.name = name;
				newMonster.pos = Position(posX, posY);

				this->Monsters.insert({ monsterCount +'a',newMonster});
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
				intialPos = intialPos + Position::direction(c);
			}

			if (this->map.isIntialPos(intialPos)) {
				charcter.second.pos = intialPos;
				break;
			}
		}
	}
}

void GloomHaven::charactersTurn()
{
	size_t totalTurns = this->Characters.size();

	std::map<char, pair<int, int>> chosecard;
	char chararcterindex;
	string card;
	for (int i=0;i<totalTurns;i++)
	{
		cin >> chararcterindex;
		getline(cin, card);
		if (card == "check") {
			// cout card
			cout << "hand: ";
			for (auto hasSkill : this->Characters[chararcterindex].skills) {
				cout << hasSkill.first << ' ';
			}
			cout << "; discard: ";
			//for (auto playedSkill : this->Characters[chararcterindex].playedSkill) {
				//cout << playedSkill.first << ' ';
			//}
			cout << endl;
		}
		else if (card == "-1")
		{
			act newAct;
			newAct.sp = 99;
			newAct.actions[0] = new ActRest;
			newAct.being = &this->Characters[chararcterindex];
			this->acts.push_back(newAct);
		}
		else
		{
			stringstream ss(card);
			int card[2];
			ss >> card[0] >> card[1];
			chosecard.insert(std::pair<char, pair<int, int>>(chararcterindex, std::make_pair(card[0], card[1])));
		}
	}
	for (auto& character: this->Characters)
	{
		int i = 0;
		string merge;
		cin >> merge;
		act newAct;
        CaracterSkill newskill1 (character.second.skills[chosecard[character.first].first]);
        CaracterSkill newskill2 (character.second.skills[chosecard[character.first].second]);
		newAct.being = &character.second;
		if (character.second.skills[chosecard[character.first].first].sp >
			character.second.skills[chosecard[character.first].second].sp)
			newAct.sp = character.second.skills[chosecard[character.first].second].sp;
		else
			newAct.sp = character.second.skills[chosecard[character.first].first].sp;
		
		if (merge[0] == chosecard[character.first].first) {
			if (merge[1] == 'u')
			{
                newAct.actions.push_back(newskill1.upAct[chosecard[character.first].first]);
				newAct.actions.push_back(newskill2.downAct[chosecard[character.first].second]);
			}
			else if (merge[1] == 'd') 
			{
				newAct.actions.push_back(newskill1.downAct[chosecard[character.first].first]);
				newAct.actions.push_back(newskill2.upAct[chosecard[character.first].second]);
			}
		}
		else if (merge[1] == chosecard[character.first].second) 
		{
			if (merge[1] == 'u')
			{
				newAct.actions.push_back(newskill2.upAct[chosecard[character.first].second]);
				newAct.actions.push_back(newskill1.downAct[chosecard[character.first].first]);
			}
			else if (merge[1] == 'd')
			{
				newAct.actions.push_back(newskill2.downAct[chosecard[character.first].second]);
				newAct.actions.push_back(newskill1.upAct[chosecard[character.first].first]);
			}
		}
		this->acts.push_back(newAct);
		i++;
	}
	
}

void GloomHaven::monstersTurn()
{
	for (auto& monster : this->Monsters) {
		MonsterSkill skill = monster.second.skills[rand() % monster.second.skills.size()];
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
	}
}

void GloomHaven::draw()
{
	char** drawBoard = new char* [this->map.width];
	for (int i = 0; i < this->map.width; i++) {
		drawBoard[i] = new char[this->map.height];
		for (int j = 0; j < this->map.height; j++)
		{
			Position pos = Position(j, i);
			if (this->map.isVisiblePos(Characters[0].pos, pos)) {
				drawBoard[i][j] = '1';
			}
			else {
				drawBoard[i][j] = ' ';
			}
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
