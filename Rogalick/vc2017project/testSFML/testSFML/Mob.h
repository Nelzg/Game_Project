#pragma once
#include <SFML\Graphics.hpp>
#include "Vector2.h"
#include <string>
#include "MaterialPoint.h"
#include "Wall.h"

class Mob : public MaterialPoint
{
public:
	int health;
	float width;
	float height;
	int weapon;
	int in_air;
	sf::RectangleShape body;
	sf::Texture texture;
	Vector2 walking_velocity;

	Mob(float width_ = 100, float hight_ = 100) {
		width = width_;
		height = hight_;
		walking_velocity = Vector2(1, 0);
		in_air = 1;
	}

	void mobSetPosition(Vector2 pos) {
		position = pos;
		body.setPosition(pos.x, pos.y);
	}

	bool checkIfInAir(Wall wall) {
		if ((wall.position.y - position.y - height <= 1) && !(position.x > wall.position.x + wall.width) && !(position.x + width < wall.position.x) && (wall.position.y+wall.height/5> position.y+height)) {
			position.y = wall.position.y - height;
			in_air = 0;
			return 0;
		}
		else {
			return 1;
		}
		/*if ((position.y - wall.position.y - wall.height <= 1) && !(position.x > wall.position.x + wall.width) && !(position.x + width < wall.position.x) && (wall.position.y + wall.height - wall.height / 5 < position.y)) {
			position.y = wall.position.y + wall.height;
			velocity.y = 0;
			in_air = 1;
			return 0;
		}
		else {
			return 1;
		}*/


	}
	
};

