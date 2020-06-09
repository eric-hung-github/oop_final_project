
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

using namespace std;

//------------------------------------
// ALL FUNCTION
//------------------------------------

//string mapFileName = "map.txt";
string charcterFileName = "charcter.txt";
string monsterFileName = "monster.txt";

string isPlay;
string mapFileName;

int main(char *argv[])
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
	game.loadMapData(mapFileName);//ok

	// generate Monster by mapfile
	game.generateMonster(); // ok

	// choose charcter intial position
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
		game.updateGame();

		break;
	}
}