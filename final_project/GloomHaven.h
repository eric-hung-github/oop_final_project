#pragma once

#include "CharcterData.h"
#include "MonsterData.h"

#include "Being.h"
#include "Character.h"
#include "Monster.h"

#include "Skill.h"
#include "MonsterSkill.h"
#include "CaracterSkill.h"

#include "MapData.h"
#include "Postition.h"

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <map>

using namespace std;

class GloomHaven
{
public:
	vector<CharcterData> CharcterDatas;
	vector<MonsterData> MonsterDatas;

	MapData map;

	std::map<char, Character> Characters;
	std::map<char, Monster> Monsters;

	//std::map<char, pair<int, int>> chosecards;

	std::map<char, pair<CaracterSkill, CaracterSkill>> characterChooseCards;
	std::map<char, MonsterSkill> monsterChooseCards;

	//vector<act> acts;

	// load data
	bool loadCharcterData(string fileName);
	bool loadMonsterDatas(string fileName);
	bool loadMapData(string fileName);

	// choose characters into Characters from CharcterDatas
	void chooseCharcters();
	void generateMonster();

	// choose intial position
	void chooseIntialPos();

	// game loop
	void charactersTurn();
	void monstersTurn();
	void startTurn();
	void characterPlayCard(pair<char, pair<CaracterSkill, CaracterSkill>> cards);
	void monsterPlayCard(pair<char, MonsterSkill>);


	// check move
	bool isPositionConflict(Being* being, Position pos);
	bool isCharacterMoveable(Being* being, Position pos);
	bool isMonsterMoveable(Being* being, Position pos);

	// attack lock
	bool isAttackable(Position sub, Position target, int range);
	bool lockCharacter(Position pos, int Range, Character* character);
	bool lockMonster(Position pos, int Range, Monster* monster);

	// 
	void updateGame();

	// draw board
	void draw();


};



// loading map

// draw
