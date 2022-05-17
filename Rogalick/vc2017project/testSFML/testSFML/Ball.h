#pragma once
#include "MaterialPoint.h"
#include <SFML\Graphics.hpp>

class Ball : public MaterialPoint
{
public:
	float radius;
	sf::CircleShape circle;
	sf::Texture texture;

	Ball(int radius_) {
		radius = radius_;
		circle.setRadius(radius);
		texture.loadFromFile("D:/Game_Project/Rogalick/bin/fireball.png");
		circle.setTexture(&texture);
		circle.setOrigin(radius, radius);
	}
};

