#pragma once

using namespace std;



class MapData
{
	// data of board
	int width;
	int height;
	char** board;

public:

	// const of map object
	const static char wall = ' ';
	const static char space = '1';
	const static char block = '2';
	const static char door = '3';


};

