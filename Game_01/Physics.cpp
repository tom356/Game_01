#include "Physics.h"

using namespace GamePhysics;
//------------Vector-------------
Vector Vector::operator*(double v2)
{
	Vector v(x, y);
	v.x *= v2;
	v.y *= v2;
	return v;
}
Vector Vector::operator*(const Vector &v2) 
{
	Vector v(x, y);
	v.x *= v2.x;
	v.y *= v2.y;
	return v;
}
Vector& Vector::operator*=(double v2) 
{
	x *= v2;
	y *= v2;
	return *this;
}
Vector& Vector::operator*=(const Vector &v2) 
{
	x *= v2.x;
	y *= v2.y;
	return *this;
}
Vector Vector::operator/(double v2)
{
	Vector v(x, y);
	v.x /= v2;
	v.y /= v2;
	return v;
}
Vector Vector::operator/(const Vector &v2)
{
	Vector v(x, y);
	v.x /= v2.x;
	v.y /= v2.y;
	return v;
}
Vector& Vector::operator/=(double v2)
{
	x /= v2;
	y /= v2;
	return *this;
}
Vector& Vector::operator/=(const Vector &v2)
{
	x /= v2.x;
	y /= v2.y;
	return *this;
}
Vector Vector::operator+(const Vector &v2) 
{
	Vector v(x, y);
	v.x += v2.x;
	v.y += v2.y;
	return v;
}
Vector &Vector::operator+=(const Vector &v2)
{
	x += v2.x;
	y += v2.y;
	return *this;
}
Vector Vector::operator-(const Vector &v2) 
{
	Vector v(x, y);
	v.x -= v2.x;
	v.y -= v2.y;
	return v;
}
Vector &Vector::operator-=(const Vector &v2) 
{
	x -= v2.x;
	y -= v2.y;
	return *this;
}
Vector::Vector() { x = 0; y = 0; }
Vector::Vector(double x, double y):x(x),y(y) {}
void Vector::normalize() 
{
	double len = length();
	x /= len;
	y /= len;
}
double Vector::length()
{
	return std::sqrt(std::pow(x, 2) + std::pow(y, 2));
}

//------------Physics-------------
bool GamePhysics::collideObjects(Object &o1, Object &o2)
{
	bool collision = false;
	if (detectCollision(o1, o1.force.x, 0, o2))
	{
		o1.force.x = 0;
		collision = true;
	}
	if (detectCollision(o1, 0, o1.force.y, o2))
	{
		if (o1.force.y > 0)
		{
			o1.frame.pos.y = o2.frame.pos.y - o1.frame.h;
			o1.force.y = 0; // primitive bouncing: -o1.force.y;
		}
		else if (o1.force.y < 0)
		{
			o1.frame.pos.y = o2.frame.pos.y + o2.frame.h;
			o1.force.y = 1;
		}
		collision = true;
	}
	return collision;
}
Object::Object() 
{
	frame.pos.x = 0;
	frame.pos.y = 0;
	frame.w = 0;
	frame.h = 0;
}
Object::Object(int x, int y, int w, int h) 
{
	frame.pos.x = x;
	frame.pos.y = y;
	frame.w = w;
	frame.h = h;
}
Object::~Object() {}
void Object::setPos(int x, int y)
{
	frame.pos.x = x;
	frame.pos.y = y;
}
void Object::setSize(int w, int h)
{
	frame.w = w;
	frame.h = h;
}
void Object::move() { frame.pos += force; }
void Object::moveBy(int x, int y) 
{ 
	frame.pos.x += x;
	frame.pos.y += y;
}
Frame &Object::getFrame() { return frame; }
Vector &Object::getForce() { return force;  }