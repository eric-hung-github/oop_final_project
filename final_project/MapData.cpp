#include <iostream>
#include <fstream>
#include "MapData.h"


using namespace std;

bool MapData::loadBoard(string fileName)
{
	ifstream mapFile(fileName);
	if (!mapFile.is_open()||!mapFile) {
		cout << "open file " << fileName << " error!" << endl;
		return false;
	}

	mapFile >> this->width >> this->height;

	this->board = new char* [this->height];
	for (int i = 0; i < this->width; i++) {
		this->board[i] = new char[this->width];
		for (int  j = 0; j < this->height; j++)
		{
			mapFile >> board[i][j];
		}
	}

	mapFile.close();
	return true;
}
