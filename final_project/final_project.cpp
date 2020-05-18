
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
    game.loadCharcterData(charcterFileName);
    // Loading monster
    game.loadMonsterDatas(monsterFileName);
    // Loading map
    game.map.loadBoard(mapFileName);

    game.chooseCharcters();
    //
    game.draw();

    // choose charcter

    // choose maze

    while (true)//game loop
    {
        // charcter choose skills

        // monster choose skills

        // execute  action <being skill> sort by sp

        // is other trigger ex open door all dead 


        break;
    }
}