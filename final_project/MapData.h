#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include "Postition.h"

using namespace std;

class MapData
{
public:
	
	vector<Position> intialPositions;

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

	bool load(string fileName);

	bool isValidPos(Position posO);//to judge wether valid

	bool isVisiblePos(Position posO, Position posT);

	bool isIntialPos(Position pos);
};

