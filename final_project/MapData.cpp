#include "MapData.h"

using namespace std;

MapData::MapData()
{
	this->height = 0;
	this->width = 0;
	this->board = nullptr;
}

MapData::MapData(string fileName)
{
	this->height = 0;
	this->width = 0;
	this->board = nullptr;
}

bool MapData::load(string fileName)
{
	// file open and check
	ifstream mapFile(fileName);
	if (!mapFile.is_open() || !mapFile) {
		cout << "open file " << fileName << " error!" << endl;
		return false;
	}

	// input width and height
	mapFile >> this->height >> this->width;

	// input board 
	this->board = new char* [this->height];
	for (int i = 0; i < this->height; i++) {
		this->board[i] = new char[this->width];
		for (int j = 0; j < this->width; j++)
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

	Position pos;
	int posX, posY;
	while (intialPosSs >> posX >> posY)
	{
		pos = Position(posX, posY);
		this->intialPositions.push_back(pos);
	}

	// input generations information of Monsters
	int generCount = 0;
	mapFile >> generCount;
	mapFile.ignore();

	for (int i = 0; i < generCount; i++)
	{
		string generateInforStr = "";
		getline(mapFile, generateInforStr);
		this->monsterGenerInfor.push_back(generateInforStr);
	}

	mapFile.close();
	return true;
}

bool MapData::isValidPos(Position posO)
{
	if (posO.x >= 0 && posO.x < this->width && posO.y >= 0 && posO.y < this->height) {
		return true;
	}
	return false;
}

void MapData::updateVisiblePosition(Position pos)
{
	if (this->board[pos.y][pos.x] == this->block) { return; }
	if (this->board[pos.y][pos.x] == this->door) { 
		this->visiblePosition.insert({pos});
		return; 
	}
	if (this->visiblePosition.find({pos}) == this->visiblePosition.end()) {
		this->visiblePosition.insert({pos});

		if (isValidPos(pos + dirUp)) {
			updateVisiblePosition(pos + dirUp);
		}
		if (isValidPos(pos + dirDown)) {
			updateVisiblePosition(pos + dirDown);
		}
		if (isValidPos(pos + dirRight)) {
			updateVisiblePosition(pos + dirRight);
		}
		if (isValidPos(pos + dirLeft)) {
			updateVisiblePosition(pos + dirLeft);
		}
	}
}

bool MapData::isCharacterMoveable(Position pos )
{
	if (this->board[pos.y][pos.x] == '0')return true;
	return false;
}

bool MapData::isMonsterMoveable(Position pos)
{
	if (this->board[pos.y][pos.x] != '1')return true;
	return false;
}

bool MapData::isIntialPos(Position pos)
{
	for (auto p : this->intialPositions) {
		if (p == pos) { return true; }
	}
	return false;
}
