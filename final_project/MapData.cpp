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
	if (!mapFile.is_open() || !mapFile)
	{
		cout << "open file " << fileName << " error!" << endl;
		return false;
	}

	// input width and height
	mapFile >> this->height >> this->width;

	// input board 
	this->board = new char* [this->height];
	for (int i = 0; i < this->height; i++)
	{
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
	if (posO.x >= 0 && posO.x < this->width && posO.y >= 0 && posO.y < this->height)
	{
		return true;
	}
	return false;
}

void MapData::updateVisiblePosition(Position pos)
{
	if (this->board[pos.y][pos.x] == this->block) { return; }
	if (this->board[pos.y][pos.x] == this->door)
	{
		this->visiblePosition.insert({ pos });
		return;
	}
	if (this->visiblePosition.find({ pos }) == this->visiblePosition.end())
	{
		this->visiblePosition.insert({ pos });

		if (isValidPos(pos + dirUp))
		{
			updateVisiblePosition(pos + dirUp);
		}
		if (isValidPos(pos + dirDown))
		{
			updateVisiblePosition(pos + dirDown);
		}
		if (isValidPos(pos + dirRight))
		{
			updateVisiblePosition(pos + dirRight);
		}
		if (isValidPos(pos + dirLeft))
		{
			updateVisiblePosition(pos + dirLeft);
		}
	}
}

bool MapData::isIntialPos(Position pos)
{
	for (auto p : this->intialPositions)
	{
		if (p == pos) { return true; }
	}
	return false;
}

void MapData::isOpenDoor(vector<Position> characterPoses)
{
	for (auto characterPos : characterPoses)
	{
		if (this->board[characterPos.y][characterPos.x]==this->door)
		{
			this->board[characterPos.y][characterPos.x] = this->space;
		}
	}
}

void MapData::drawSetIntailPos(vector<pair<char, Position>> beingPoses)
{
	char** drawBoard = new char* [this->height];
	for (int i = 0; i < this->height; i++)
	{
		drawBoard[i] = new char[this->width];
		for (int j = 0; j < this->width; j++)
		{
			Position pos = Position(j, i);
			if (visiblePosition.find({ j,i }) != visiblePosition.end())
			{
				drawBoard[i][j] = board[i][j];
			}
			else
			{
				drawBoard[i][j] = ' ';
			}
		}
	}

	// minPos
	Position minIntialPos = (this->intialPositions[0]);// weird----
	for (auto intialPosition : this->intialPositions)
	{
		if (intialPosition.x + intialPosition.y < minIntialPos.x + minIntialPos.y)
		{
			minIntialPos = intialPosition;
		}
		else if (intialPosition.x + intialPosition.y == minIntialPos.x + minIntialPos.y)
		{
			if (intialPosition.y < minIntialPos.y)
			{
				minIntialPos = intialPosition;
			}

		}
	}

	for (auto intialPos:this->intialPositions)
	{
		drawBoard[intialPos.y][intialPos.x] = '_';
	}
	drawBoard[minIntialPos.y][minIntialPos.x] = '*';

	for (auto beingPos : beingPoses)
	{
		drawBoard[beingPos.second.y][beingPos.second.x] = beingPos.first;
	}


	for (int i = 0; i < this->height; i++)
	{
		for (int j = 0; j < this->width; j++)
		{
			cout << drawBoard[i][j];
		}
		cout << endl;
	}
	cout << endl;

}
