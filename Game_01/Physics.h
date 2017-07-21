#pragma once
#include<cmath>
#include<memory>

namespace GamePhysics
{
	struct Vector
	{
		double x, y;

		Vector operator+(const Vector &v2);
		Vector& operator+=(const Vector &v2);
		Vector operator-(const Vector &v2);
		Vector& operator-=(const Vector &v2);
		Vector operator*(double v2);
		Vector operator*(const Vector &v2);
		Vector& operator*=(double v2);
		Vector& operator*=(const Vector &v2);
		Vector operator/(double v2);
		Vector operator/(const Vector &v2);
		Vector& operator/=(double v2);
		Vector& operator/=(const Vector &v2);

		Vector();
		Vector(double x, double y);
		void normalize();
		double length();
	};
	static double gravity = 2;
	struct Frame
	{
		Vector pos;
		int w, h;
	};
	class Object
	{
		Frame frame;
		Vector force;
		friend bool detectCollision(Object &o1, Object &o2);
		friend bool detectCollision(Object &o1, double x_offset, double y_offset, Object &o2);
		friend bool detectCollisionMoveing(Object &o1, Object &o2);
		friend void collideObjects(Object &o1, Object &o2);		
		friend void applyForce(Object &obj, Vector v);
		friend void applyGravity(Object &obj);
		
	public:
		Object(int x, int y, int w, int h);
		~Object();
		void move();
		Frame &getFrame();
		Vector &getForce();
	};
	//detects collision between objects
	inline bool detectCollision(Object &o1, Object &o2)
	{
		return (o1.frame.pos.x < o2.frame.pos.x + o2.frame.w &&
			o1.frame.pos.x + o1.frame.w > o2.frame.pos.x &&
			o1.frame.pos.y < o2.frame.pos.y + o2.frame.h &&
			o1.frame.h + o1.frame.pos.y > o2.frame.pos.y);
	}
	//detects collision with offset
	inline bool detectCollision(Object &o1, double x_offset, double y_offset, Object &o2)
	{
		return (o1.frame.pos.x + x_offset < o2.frame.pos.x + o2.frame.w &&
			o1.frame.pos.x + x_offset + o1.frame.w > o2.frame.pos.x &&
			o1.frame.pos.y + y_offset < o2.frame.pos.y + o2.frame.h &&
			o1.frame.h + o1.frame.pos.y + y_offset > o2.frame.pos.y);
	}
	//detects collision minding object movement
	inline bool detectCollisionMoveing(Object &o1, Object &o2)
	{
		return 	detectCollision(o1, o1.force.x, o1.force.y, o2);
	}

	// detects collision side and stops object
	inline void collideObjects(Object &o1, Object &o2)
	{
		if (o1.frame.pos.x + o1.frame.w > o2.frame.pos.x && o1.frame.pos.x < o2.frame.pos.x) { (o1.force.x>0 ? 0 : o1.force.x); }/*kolizja z prawej*/
		if (o1.frame.pos.x < o2.frame.pos.x + o2.frame.w && o1.frame.pos.x > o2.frame.pos.x) { (o1.force.x < 0 ? 0 : o1.force.x); }/*kolizja z lewej*/
		if (o1.frame.pos.y < o2.frame.pos.y + o2.frame.h && o1.frame.pos.y > o2.frame.pos.y) { (o1.force.y < 0 ? 0 : o1.force.y); }/*kolizja z gory*/
		if (o1.frame.pos.y + o1.frame.h > o2.frame.pos.y && o1.frame.pos.y < o2.frame.pos.y) { (o1.force.y>0 ? 0 : o1.force.y); }/*kolizja z dolu*/
	}

	inline void applyForce(Object &obj, Vector v) { obj.force += v; }
	inline void applyGravity(Object &obj) { obj.force.y += gravity; }
}