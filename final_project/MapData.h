#pragma once
#include <vector>
#include <set>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include "Postition.h"

using namespace std;

#ifndef POSITION_SORT
#define POSITION_SORT

struct positionSort
{
	bool operator()(const Position& a,const Position& b)const {
		if (a.x == b.x) return a.y < b.y;
		else return a.x < b.x;
	}
};



#endif // !POSITION_SORT



class MapData
{
public:

	vector<Position> intialPositions;
	vector<string> monsterGenerInfor;
	set < Position, positionSort> visiblePosition;

	// data of board
	int width;
	int height;
	char** board;

	// const of map object
	const static char wall = ' ';
	const static char space = '1';
	const static char block = '0';
	const static char door = '3';

	MapData();
	MapData(string fileName);

	bool load(string fileName);

	bool isValidPos(Position posO);//to judge wether valid

	void updateVisiblePosition(Position intialPos);

	bool isIntialPos(Position pos);

	void isOpenDoor(vector<Position> characterPoses);
};