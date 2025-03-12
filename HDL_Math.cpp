#include "HDL_Math.h"

Vector2::Vector2() : mX(0.0f), mY(0.0f) {}

Vector2::Vector2(float x, float y) : mX(x), mY(y) {}

//‘«‚µZ
Vector2 operator+(const Vector2& a, const Vector2& b)
{
	Vector2 tmp;
	tmp.mX = a.mX + b.mX;
	tmp.mY = a.mY + b.mY;

	return tmp;
}

//ˆø‚«Z
Vector2 operator-(const Vector2& a, const Vector2& b)
{
	Vector2 tmp;
	tmp.mX = a.mX - b.mX;
	tmp.mY = a.mY - b.mY;

	return tmp;
}

//Š|‚¯Z
Vector2 operator*(float L, const Vector2& R)
{
	Vector2 tmp;
	tmp.mX = L * R.mX;
	tmp.mY = L * R.mY;

	return tmp;
}

Vector2 operator*(const Vector2& L, float R)
{
	Vector2 tmp;
	tmp.mX = L.mX * R;
	tmp.mY = L.mY * R;

	return tmp;
}

//ŠOÏ (~Cross)
//float operator~(const Vector2& a, const Vector2& b)
//{
//	return 0.0f;
//}

//Š„‚èZ
Vector2 operator/(const Vector2& L, float R)
{
	Vector2 tmp;
	tmp.mX = L.mX / R;
	tmp.mY = L.mY / R;

	return tmp;
}
