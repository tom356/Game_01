#pragma once
#include<cmath>
#include<memory>

namespace GamePhysics
{
	static double gravity = 3;
	static double terminal_velocity = 20;

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

	struct Frame
	{
		Vector pos;
		int w, h;
	};
	class Object
	{
	protected:
		Frame frame;
		Vector force;
		friend bool detectCollision(Object &o1, Object &o2);
		friend bool detectCollision(Object &o1, double x_offset, double y_offset, Object &o2);
		friend bool detectCollisionMoveing(Object &o1, Object &o2);
		friend bool collideObjects(Object &o1, Object &o2);		
		friend void applyForce(Object &obj, Vector v);
		friend inline void applyForce(Object &obj, double x, double y);
		friend void applyGravity(Object &obj);
		friend void setForce(Object &obj, Vector v);
	public:
		Object();
		Object(int x, int y, int w, int h);
		~Object();
		void setPos(int x, int y);
		void setSize(int w, int h);
		void move();
		void moveBy(int x, int y);
		Frame &getFrame();
		Vector &getForce();
	};
	//detects collision between objects; not used
	inline bool detectCollision(Object &o1, Object &o2)
	{
		return (o1.frame.pos.x < o2.frame.pos.x + o2.frame.w &&
			o1.frame.pos.x + o1.frame.w > o2.frame.pos.x &&
			o1.frame.pos.y < o2.frame.pos.y + o2.frame.h &&
			o1.frame.h + o1.frame.pos.y > o2.frame.pos.y);
	}
	//detects collision with offset; not used
	inline bool detectCollision(Object &o1, double x_offset, double y_offset, Object &o2)
	{
		return (o1.frame.pos.x + x_offset < o2.frame.pos.x + o2.frame.w &&
			o1.frame.pos.x + x_offset + o1.frame.w > o2.frame.pos.x &&
			o1.frame.pos.y + y_offset < o2.frame.pos.y + o2.frame.h &&
			o1.frame.h + o1.frame.pos.y + y_offset > o2.frame.pos.y);
	}
	//detects collision minding object movement; not used
	inline bool detectCollisionMoveing(Object &o1, Object &o2)
	{
		return detectCollision(o1, o1.force.x, o1.force.y, o2);
	}

	// detects collision side and stops object; used
	bool collideObjects(Object &o1, Object &o2);

	inline void applyForce(Object &obj, Vector v) { obj.force += v; }
	inline void applyForce(Object &obj, double x, double y) { obj.force.x += x; obj.force.y += y;}
	inline void setForce(Object &obj, Vector v) { obj.force = v; }
	inline void applyGravity(Object &obj) { obj.force.y = (obj.force.y > terminal_velocity ? terminal_velocity : obj.force.y + gravity); }
}