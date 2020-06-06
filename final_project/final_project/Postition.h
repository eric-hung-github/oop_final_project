#pragma once

using namespace std;

class Position
{
public:
	int x;
	int y;


	Position();
	Position(int x, int y);

	Position& operator+(const Position& pos);
	Position& operator-(const Position& pos);
	bool operator==(const Position& pos);

	// return dir in pos according wasd
	static Position direction(char c);
};

const static Position dirUp = Position(0, -1);
const static Position dirDown = Position(0, 1);
const static Position dirRight = Position(1,0);
const static Position dirLeft = Position(-1,0);