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
Object::Object(int x, int y, int w, int h) 
{
	frame.pos.x = x;
	frame.pos.y = y;
	frame.w = w;
	frame.h = h;
}
Object::~Object() {}
void Object::move() { frame.pos += force; }
Frame &Object::getFrame() { return frame; }
Vector &Object::getForce() { return force;  }