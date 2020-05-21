#include <iostream>
#include <fstream>
#include <sstream>

#include "MapData.h"
#include "Postition.h"

using namespace std;

MapData::MapData()
{
}

MapData::MapData(string fileName)
{
	// file open and check
	ifstream mapFile(fileName);
	if (!mapFile.is_open() || !mapFile) {
		cout << "open file " << fileName << " error!" << endl;
	}

	// input width and height
	mapFile >> this->width >> this->height;

	// input board 
	this->board = new char* [this->height];
	for (int i = 0; i < this->width; i++) {
		this->board[i] = new char[this->width];
		for (int j = 0; j < this->height; j++)
		{
			mapFile >> board[i][j];
		}
	}
	mapFile.ignore();

	// input intial postition information

	string intialPosStr;
	stringstream intialPosSs;

	getline(mapFile, intialPosStr);
	intialPosSs = stringstream(intialPosStr);

	Postition pos;
	int posX, posY;
	while (intialPosSs>> posX >> posY)
	{
		pos = Postition(posX, posY);
		this->intialPositions.push_back(pos);
	}

	// input generations information of Monster

	int generCount=0;
	mapFile >> generCount;
	mapFile.ignore();

	for (int i = 0; i < generCount; i++)
	{
		string generateInfor;
		getline(mapFile, generateInfor);
		this->monsterGenerInfor.push_back(generateInfor);
	}


	mapFile.close();
}

bool MapData::loadBoard(string fileName)
{

	return true;
}
