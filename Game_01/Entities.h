#pragma once

#include "Physics.h"
namespace Entities
{
	class Player : public GamePhysics::Object
	{
		bool jumping;
		bool moveing;
	public:
		Player();
		Player(int x, int y, int w, int h);
		void jump();
		void moveLeft();
		void moveRight();
		void stopped();
		void playerOnGround();
	};
}