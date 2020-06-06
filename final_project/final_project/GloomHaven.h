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

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

#ifndef ACT_STRUCT
#define ACT_STRUCT
struct act
{
	int sp=0;
	Being *being=nullptr;
	vector<Action*> actions;
};
#endif

using namespace std;

class GloomHaven
{
public:
	vector<CharcterData> CharcterDatas;
	vector<MonsterData> MonsterDatas;

	MapData map;

	vector<Character> Characters;
	vector<Monster> Monsters;

	vector<act> acts;

	// constructor

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
	void execute();

	// 
	void updateGameState();

	// draw board
	void draw();

	
};



// loading map

// draw
