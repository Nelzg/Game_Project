#pragma once
#include "MaterialPoint.h"
#include <SFML\Graphics.hpp>

class Ball : public MaterialPoint
{
public:
	float radius;
	int type;
	int damage;
	sf::CircleShape circle;
	sf::Texture texture;

	Ball(int radius_) {
		radius = radius_;
		circle.setRadius(radius);
		texture.loadFromFile("fireball_2.png");
		circle.setTexture(&texture);
		circle.setOrigin(radius, radius);
	}
	
	void setBallPosition(Vector2 new_position) {
		position = new_position;
		circle.setPosition(position.x, position.y);
		circle.setTexture(&texture);
	}
};

