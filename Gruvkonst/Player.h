#pragma once
#include "Point.h"

class Player
{
public:
	Player();
	Player(Point*);
	~Player();
	
	Point* Position;
	double Speed;
	double Angle;
};

