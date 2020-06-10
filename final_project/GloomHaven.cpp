#include "GloomHaven.h"

using namespace std;

bool cmpcharacter(pair<char, std::map<int, CaracterSkill>>& a, pair<char, std::map<int, CaracterSkill>>& b)
{
	std::map<int, CaracterSkill>::iterator ita = a.second.begin();
	std::map<int, CaracterSkill>::iterator itb = b.second.begin();
	if (ita->second.sp == itb->second.sp)
	{
		ita++;
		itb++;
		if (ita->second.sp == itb->second.sp)
		{
			return a.first < b.first;
		}
		else
		{
			return ita->second.sp < itb->second.sp;
		}
	}
	return ita->second.sp < itb->second.sp;

}

bool cmpmonster(pair<char, MonsterSkill>& a, pair<char, MonsterSkill>& b)
{
	return a.second.sp < b.second.sp;
}

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
	cout << "Please enter the amount of characters(2~4): ";
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
	Position intialPos = (this->map.intialPositions[0]);
	this->map.updateVisiblePosition(intialPos);
	vector<pair<char, Position>>settedPos;
	for (auto monster : this->Monsters)
	{
		if (this->map.visiblePosition.find(monster.second.pos) == this->map.visiblePosition.end())
		{
			continue;
		}
		settedPos.push_back(make_pair(monster.first, monster.second.pos));
	}

	for (auto& charcter : this->Characters)
	{
		this->map.updateVisiblePosition(intialPos);
		system("CLS");
		this->map.drawSetIntailPos(settedPos);

		while (true)
		{
			string choosePosition;
			cin >> choosePosition;


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
				settedPos.push_back(make_pair(charcter.first, intialPos));
				break;
			}
		}


	}
	this->map.updateVisiblePosition(intialPos);
	system("CLS");
	this->map.drawSetIntailPos(settedPos);
}

void GloomHaven::charactersTurn()
{
	for (auto character : this->Characters)
	{
		if (character.second.skills.size() < 2 && character.second.playedSkill.size() < 2)
		{
			this->Characters.erase(character.first);
		}
	}

	cin.ignore();

	size_t totalTurns = this->Characters.size();

	char chararcterIndex;
	string inputCommand;
	while (totalTurns > 0)
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
			else if (this->Characters[chararcterIndex].playedSkill.size() < 2)
			{
				cout << "You Can't ResTTTT!!!" << endl;
			}
			else
			{
				std::map<int, CaracterSkill> choosedSkill;
				CaracterSkill rest;
				rest.sp = 99;
				choosedSkill.insert(make_pair(-1, rest));
				choosedSkill.insert(make_pair(-2, rest));
				characterChooseCards.insert(make_pair(chararcterIndex, choosedSkill));
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
				auto skillOne = std::make_pair(cards[0], this->Characters[chararcterIndex].skills[cards[0]]);
				auto skillTwo = std::make_pair(cards[1], this->Characters[chararcterIndex].skills[cards[1]]);
				std::map<int, CaracterSkill> choosedSkill;
				choosedSkill.insert(skillOne);
				choosedSkill.insert(skillTwo);
				characterChooseCards.insert(make_pair(chararcterIndex, choosedSkill));

				this->Characters[chararcterIndex].playedSkill.insert({ cards[0],this->Characters[chararcterIndex].skills[cards[0]] });
				this->Characters[chararcterIndex].playedSkill.insert({ cards[1],this->Characters[chararcterIndex].skills[cards[1]] });
				this->Characters[chararcterIndex].skills.erase(cards[0]);
				this->Characters[chararcterIndex].skills.erase(cards[1]);

				totalTurns -= 1;
			}

		}
	}

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

void GloomHaven::monsterPlayCard(pair<char, MonsterSkill> skill)
{
	//if (this->Characters[skill.first].hp <= 0)return;

	cout << skill.first << "'s turn\tcard:" << endl;

	for (auto action : skill.second.act)
	{
		this->execute(&this->Monsters[skill.first], action);
	}
	if (skill.second.redraw)
	{
		this->Monsters[skill.first].skills = this->Monsters[skill.first].equipedSkills;
	}
}

void GloomHaven::execute(Being* being, Action* action)
{
	//system("CLS");
	action->execute(being);
	this->executeUpdate();
	this->draw();
}

void GloomHaven::characterPlayCard(pair<char, std::map<int, CaracterSkill>> cards)
{


	auto character = &this->Characters.find(cards.first)->second;
	int playCard;
	char playPart;

	if ((*cards.second.begin()).first < 0)
	{
		cout << cards.first << "'s turn\tZzzZZzzZZZzzzz..." << endl;
		ActRest rest;
		this->execute(character, &rest);
		return;
	}

	cout << cards.first << "'s turn\tcard:";
	for (auto index : cards.second)
	{
		cout << ' ' << index.first;
	}
	cout << endl;

	cin >> playCard >> playPart;

	if (playPart == 'u')
	{
		for (auto action : cards.second[playCard].upAct)
		{
			this->execute(character, action);
		}

		cards.second.erase(playCard);

		for (auto action : (*cards.second.begin()).second.downAct)
		{
			this->execute(character, action);
		}
	}
	else if (playPart == 'd')
	{
		for (auto action : cards.second[playCard].downAct)
		{
			this->execute(character, action);
		}

		cards.second.erase(playCard);

		for (auto action : (*cards.second.begin()).second.upAct)
		{
			this->execute(character, action);
		}
	}

}

bool GloomHaven::runTurn()
{

	vector<pair<char, std::map<int, CaracterSkill>>> charactercard;
	vector < pair<char, MonsterSkill>> monstercard;

	for (auto c : this->characterChooseCards)
	{
		charactercard.push_back(c);
	}

	for (auto c : this->monsterChooseCards)
	{
		monstercard.push_back(c);
	}

	sort(charactercard.begin(), charactercard.end(), cmpcharacter);
	sort(monstercard.begin(), monstercard.end(), cmpmonster);

	auto characterChooseCard = charactercard.begin();
	auto monsterChooseCard = monstercard.begin();



	while (characterChooseCard != charactercard.end() || monsterChooseCard != monstercard.end())
	{

		if (characterChooseCard == charactercard.end())
		{
			if (this->Monsters[monsterChooseCard->first].hp <= 0)
			{
				monsterChooseCard++;
				continue;
			}
			cout << this->Monsters[monsterChooseCard->first].name << ' ';
			monsterChooseCard->second.printSkill();
			monsterChooseCard++;
			continue;
		}
		if (monsterChooseCard == monstercard.end())
		{
			if (this->Characters[characterChooseCard->first].hp <= 0)
			{
				characterChooseCard++;
				continue;
			}
			cout << characterChooseCard->first << ' ';
			cout << characterChooseCard->second.begin()->second.sp << ' ';
			for (auto skillIndex : characterChooseCard->second)
			{
				cout << skillIndex.first << ' ';
			}
			cout << endl;
			characterChooseCard++;
			continue;
		}

		if (characterChooseCard->second.begin()->second.sp > monsterChooseCard->second.sp)
		{
			if (this->Monsters[monsterChooseCard->first].hp <= 0)
			{
				monsterChooseCard++;
				continue;
			}
			cout << this->Monsters[monsterChooseCard->first].name << ' ';
			monsterChooseCard->second.printSkill();
			monsterChooseCard++;
		}
		else
		{
			if (this->Characters[characterChooseCard->first].hp <= 0)
			{
				characterChooseCard++;
				continue;
			}
			cout << characterChooseCard->first << ' ';
			cout << characterChooseCard->second.begin()->second.sp << ' ';
			for (auto skillIndex : characterChooseCard->second)
			{
				cout << skillIndex.first << ' ';
			}
			cout << endl;
			characterChooseCard++;
		}
	}

	characterChooseCard = charactercard.begin();
	monsterChooseCard = monstercard.begin();

	while (characterChooseCard != charactercard.end() || monsterChooseCard != monstercard.end())
	{
		if (this->gameOver)
		{
			cout << "You win!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
			return true;
		}

		if (characterChooseCard == charactercard.end())
		{
			if (this->Monsters[monsterChooseCard->first].hp <= 0)
			{
				monsterChooseCard++;
				continue;
			}
			this->monsterPlayCard(*monsterChooseCard++);
			continue;
		}
		if (monsterChooseCard == monstercard.end())
		{
			if (this->Characters[characterChooseCard->first].hp <= 0)
			{
				characterChooseCard++;
				continue;
			}
			this->characterPlayCard(*characterChooseCard++);
			continue;
		}

		if (characterChooseCard->second.begin()->second.sp > monsterChooseCard->second.sp)
		{
			if (this->Monsters[monsterChooseCard->first].hp <= 0)
			{
				monsterChooseCard++;
				continue;
			}
			this->monsterPlayCard(*monsterChooseCard++);
		}
		else
		{
			if (this->Characters[characterChooseCard->first].hp <= 0)
			{
				characterChooseCard++;
				continue;
			}
			this->characterPlayCard(*characterChooseCard++);
		}
	}

	return false;
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
	//yayay
	return true;

	if (Position::countRange(sub, target) > range)return false;

	std::set<Position> checkPoses;

	int directionX = target.x - sub.x;
	int directionY = target.y - sub.y;

	for (size_t i = 0; i < this->map.height; i++)
	{
		for (size_t j = 0; j < this->map.width; j++)
		{
			Position checkPos = Position(i, j);
		}
	}

	for (auto checkPos : checkPoses)
	{
		if (this->map.board[checkPos.y][checkPos.x] == this->map.block)return false;
	}
	return true;
}

bool GloomHaven::lockCharacter(Position pos, int range, Character* characterPtr)
{
	double minRange = Position::countRange(this->Characters.begin()->second.pos, pos);
	characterPtr = &this->Characters.begin()->second;
	for (auto character : this->Characters)
	{

		if (Position::countRange(character.second.pos, pos) < minRange)
		{
			minRange = Position::countRange(character.second.pos, pos);
			characterPtr = &character.second;
		}
	}

	if (this->isAttackable(pos, characterPtr->pos, range))
	{
		return true;
	}
	return false;
}

bool GloomHaven::lockMonster(Position pos, int Range, Monster* monster)
{
	return true;
}

void GloomHaven::executeUpdate()
{
	this->map.visiblePosition.clear();
	for (auto character : this->Characters)
	{
		this->map.isOpenDoor({ character.second.pos });
		map.updateVisiblePosition(character.second.pos);
	}

	for (auto monster : this->Monsters)
	{
		if (monster.second.hp <= 0)
		{
			this->Monsters.erase(monster.first);
			break;
		}
	}
	if (this->Monsters.size() == 0)
	{

		this->gameOver = true;
	}

}

bool GloomHaven::roundUpdate()
{
	this->characterChooseCards.clear();
	this->monsterChooseCards.clear();

	for (auto c : this->Characters)
	{
		c.second.sheldPoint = 0;
	}

	for (auto c : this->Monsters)
	{
		c.second.sheldPoint = 0;
	}

	if (this->Characters.size() == 0)
	{
		return false;
	}

	vector<Position> characterPos;
	for (auto c : this->Characters)
	{
		characterPos.push_back(c.second.pos);
	}

	return true;
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