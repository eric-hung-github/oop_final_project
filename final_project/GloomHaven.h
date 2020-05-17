#pragma once

#include "BeingData.h"
#include "CharcterData.h"
#include "MonsterData.h"

#include "Being.h"
#include "Character.h"
#include "Monster.h"

#include "MapData.h"

#include <vector>


using namespace std;


class GloomHaven
{
public:
	vector<CharcterData> CharcterDatas;
	vector<MonsterData> MonsterDatas;
	vector<Character> Characters;
	vector<Monster> Monsters;

	MapData map;

	// constructor

	// load data
	bool loadCharcterData(string fileName);
	bool loadMonsterDatas(string fileName);

	// choose characters into Characters from CharcterDatas
	void chooseCharcters();

	// draw board
	void draw();

	
};



// loading map

// draw
