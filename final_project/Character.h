#pragma once

#include "Being.h"
#include <vector>

using namespace std;

class Character :public Being
{
	void move();
	void attack();
	void heal();
	void shield();
};

