#pragma once
#include <vector>
#include <string>

#include "Postition.h"

using namespace std;

class MapData
{
public:
	
	vector<Postition> intialPositions;

	vector<string> monsterGenerInfor;

	// data of board
	int width;
	int height;
	char** board;

	// const of map object
	const static char wall = ' ';
	const static char space = '1';
	const static char block = '2';
	const static char door = '3';

	MapData();
	MapData(string fileName);
	bool loadBoard(string fileName);
};

