
//------------------------------------
// 2020 5 17
// 
// unfinish:
//      1. read skill when range after attack
//
//------------------------------------

#include <iostream>
#include <string>

#include "GloomHaven.h"

#include "MapData.h"
#include "Postition.h"

#include "BeingData.h"
#include "CharcterData.h"
#include "MonsterData.h"

#include "Being.h"
#include "Character.h"
#include "Monster.h"

#include "Skill.h"
#include "CaracterSkill.h"
#include "MonsterSkill.h"


using namespace std;

//------------------------------------
// ALL FUNCTION
//------------------------------------

string mapFileName = "map.txt";
string charcterFileName = "charcter.txt";
string monsterFileName = "monster.txt";

int main()
{
	GloomHaven game;
	// Loading charcter
	game.loadCharcterData(charcterFileName);//ok
	// Loading monster
	game.loadMonsterDatas(monsterFileName);// yubin
	// Loading map
	game.map = MapData(mapFileName);//ok

	// choose charcter
	game.chooseCharcters();
	// generate Monster by mapfile
	game.generateMonster();
	//
	game.chooseIntialPos();

	while (true)//game loop
	{
		// charcter choose skills
		game.charactersTurn();
		// monster choose skills
		game.monstersTurn();
		// execute  action <being skill> sort by sp

		// is other trigger ex open door all dead 

		// is win or game over


		game.draw();

		break;
	}
}