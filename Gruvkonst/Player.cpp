#define _USE_MATH_DEFINES
#include <cmath>
#include "Player.h"


Player::Player() {
	this->Speed = 0;
	this->Angle = M_PI / 2;
	this->Position = new Point();
}

Player::Player(Point* position) : Player() {
	this->Angle = 0; Position = position;
}

Player::~Player() {
	delete(this->Position);
}
