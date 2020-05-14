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

int main()
{
    GloomHaven game;
    game.map.loadBoard(mapFileName);

    game.draw();
    // loading all data

    // choose charcter

    // choose maze

    while (true)
    {
        // charcter choose skills

        // monster choose skills

        // execute  action <being skill> sort by sp

        // is other trigger ex open door all dead 

    }
}