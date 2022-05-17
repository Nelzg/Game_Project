#pragma once
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>

struct Vector2
{
	float x,y;
	Vector2(float _x = 0, float _y = 0) 
	{
		x = _x;
		y = _y;
	}

	float len() {
		return sqrt(x * x + y * y);
	}

	Vector2 operator+(const Vector2& other) const
	{
		Vector2 result;
		result.x = x + other.x;
		result.y = y + other.y;
		return result;
	}

	Vector2 operator+=(const Vector2& other)
	{
		x += other.x;
		y += other.y;
		return *this;
	}
	
	Vector2 operator-(const Vector2& other) const
	{
		Vector2 result;
		result.x = x - other.x;
		result.y = y - other.y;
		return result;
	}
	
	Vector2 operator-=(const Vector2& other) 
	{
		x -= other.x;
		y -= other.y;
		return *this;
	}

	float operator*(const Vector2& other) const
	{
		return x * other.x + y * other.y;
	}

	Vector2 operator*(float c) const
	{
		return Vector2(x * c, y * c);
	}

	Vector2 operator/(const float c) const
	{
		Vector2 result;
		result.x = x / c;
		result.y = y / c;
		return result;
	}

	float operator^(const Vector2& other) const
	{
		return sqrt((x * other.y) * (x * other.y) + (y * other.x) * (x * other.y));
	}

	bool operator==(const Vector2& other) const
	{
		return (((x - other.x) <= 1.e-6) && ((y - other.y) <= 1.e-6));
	}
	
	Vector2 norm()
	{
		Vector2 result;
		result.x = x / len();
		result.y = y / len();
		return result;
	}

	float squareLen()
	{
		return len() * len();
	}

	Vector2 rotate(double fi)
	{
		Vector2 result;
		double di = fi * M_PI / 180;
		result.x = x * cos(di) - y * sin(di);
		result.y = x * sin(di) + y * cos(di);
		return result;
	}

	Vector2 getRotated(double fi)
	{
		double di = fi * M_PI / 180;
		double k = x * cos(di) - y * sin(di);
		y = x * sin(di) + y * cos(di);
		x = k;
		return *this;
	}

	Vector2 perpendicular()
	{
		return rotate(90);
	}
	
	Vector2 operator-()
	{
		return rotate(180);
	}
};

std::ostream& operator<<(std::ostream& stream, const Vector2& other) {
	stream << other.x << " " << other.y;
	return stream;
}

std::istream& operator>>(std::istream& stream, Vector2& other)
{
	stream >> other.x >> other.y;
	return stream;
}



