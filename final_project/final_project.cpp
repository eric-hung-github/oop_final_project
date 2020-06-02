
//------------------------------------
// 2020 5 17
// 
// unfinish:
//      
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

//string mapFileName = "map.txt";
string charcterFileName = "charcter.txt";
string monsterFileName = "monster.txt";

string isPlay;
string mapFileName;

int main()
{
	cin >> isPlay;

	GloomHaven game;
	// Loading charcter
	game.loadCharcterData(charcterFileName);//ok
	// Loading monster
	game.loadMonsterDatas(monsterFileName);//ok

	// choose charcter
	game.chooseCharcters();//ok

	cin >> mapFileName;

	// Loading map
	game.map = MapData(mapFileName);//ok
	// generate Monster by mapfile
	game.generateMonster(); // ok

	// 
	game.chooseIntialPos();// ok


	while (true)//game loop
	{
		// charcter choose skills
		game.charactersTurn();
		// monster choose skills
		game.monstersTurn();
		// execute  action <being skill> sort by sp
		game.execute();
		// is other trigger ex open door all dead

		// is win or game over


		game.draw();

		break;
	}
}