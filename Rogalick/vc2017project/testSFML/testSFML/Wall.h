#pragma once
#include <SFML\Graphics.hpp>
#include "MaterialPoint.h"

class Wall: public MaterialPoint
{
public:
	sf::RectangleShape rectangle;
	sf::Texture texture;
	int width;
	int height;

	Wall(int width_ = 10, int height_ = 10) {
		width = width_;
		height = height_;
		rectangle.setSize(sf::Vector2f(width, height));
		texture.loadFromFile("D:/Game_Project/Rogalick/bin/map_elements/wall.png");
	}

	void setWallPosition(Vector2 new_position) {
		position = new_position;
		rectangle.setPosition(position.x, position.y);
		rectangle.setTexture(&texture);
	}
};
