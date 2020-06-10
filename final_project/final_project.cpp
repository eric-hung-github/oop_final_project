
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

int main(char* argv[])
{
	while (true)
	{
		cout << "Please enter exit or play" << endl;
		cin >> isPlay;
		if (isPlay == "exit")break;
		else if (isPlay == "play");
		else
		{
			cout << "Please enter exit or play" << endl;
			continue;
		};

		GloomHaven game;
		// Loading charcter
		game.loadCharcterData(charcterFileName);//ok
		// Loading monster
		game.loadMonsterDatas(monsterFileName);//ok
		// choose charcter
		game.chooseCharcters();//ok

		cout << "Please enter map file name: ";
		cin >> mapFileName;

		// Loading map
		game.loadMapData(mapFileName);//ok

		// generate Monster by mapfile
		game.generateMonster(); // ok

		// choose charcter intial position
		game.chooseIntialPos();// ok


		while (true)//game loop
		{
			cout << "Round: " << game.round << endl;
			// charcter choose skills
			game.charactersTurn();

			// monster choose skills
			game.monstersTurn();

			// execute  action <being skill> sort by sp
			if (game.runTurn())break;

			// is win or game over

			game.roundUpdate();

			game.round++;
		}
	}

}