#include "Entities.h"
using namespace Entities;
//------------Player-------------
Player::Player() : GamePhysics::Object(0, 0, 100, 100) {}
Player::Player(int x, int y, int w, int h) : GamePhysics::Object(x, y, w, h) {}
void Player::jump()
{
	if (jumping && force.y == 0)
		jumping = false;
	if (!jumping)
	{
		force.y = -40;
		jumping = true;
	}
}
void Player::playerOnGround() { jumping = false; }
void Player::moveLeft()
{
	force.x = -5;
}
void Player::moveRight()
{
	force.x = 5;
}
void Player::stopped()
{
	force.x = 0;
}