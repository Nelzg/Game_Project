#pragma once
#include <SFML\Graphics.hpp>
#include "Vector2.h"
#include <string>
#include "MaterialPoint.h"

class Mob : public MaterialPoint
{
public:
	int health;
	float width;
	float height;
	int weapon;
	sf::RectangleShape body;
	sf::Texture texture;

	Mob(float width_ = 100, float hight_ = 100) {
		width = width_;
		height = hight_;
	}

};

