#include <iostream>
#include <fstream>
#include "MapData.h"


using namespace std;

bool MapData::loadBoard(string fileName)
{
	ifstream file=ifstream(fileName);
	if (!file.is_open()) {
		cout << "open file " << fileName << " error!" << endl;
		return false;
	}

	file >> this->width >> this->height;

	this->board = new char* [this->height];
	for (int i = 0; i < this->width; i++) {
		this->board[i] = new char[this->width];
		for (int  j = 0; j < this->height; j++)
		{
			file >> board[i][j];
		}
	}

	file.close();
	return true;
}
