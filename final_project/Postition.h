#pragma once

using namespace std;

class Postition
{
public:
	int x;
	int y;


	Postition();
	Postition(int x, int y);
};

const static Postition dirUp = Postition(0, 1);
const static Postition dirDown = Postition(0, -1);
const static Postition dirRight = Postition(1,0);
const static Postition dirLeft = Postition(-1,0);

// for judge wether visible from two position
bool isVisible();