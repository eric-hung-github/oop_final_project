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

	vector<CharcterData> CharcterDatas;
	vector<MonsterData> MonsterDatas;
	vector<Character> Characters;
	vector<Monster> Monsters;

	MapData map;


	void draw();
};

// loading charctor

// loading map

// draw
