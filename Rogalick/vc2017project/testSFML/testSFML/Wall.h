#pragma once
#include <SFML\Graphics.hpp>
#include "MaterialPoint.h"

class Wall: public MaterialPoint
{
public:
	sf::RectangleShape rectangle;
	sf::Texture texture;
	int width;
	int has_smb_on_it;
	int height;
	Vector2 top_border, bot_border, left_border, right_border;
	Vector2 top_right_point, bot_right_point, bot_left_point;

	Wall(int width_ = 10, int height_ = 10) {
		width = width_;
		height = height_;
		has_smb_on_it = 0;
		top_border = Vector2(1, 0);
		bot_border = Vector2(-1, 0);
		left_border = Vector2(0, -1);
		right_border = Vector2(0, 1);
		top_right_point = top_border * width + position;
		bot_right_point = top_border * width + position + right_border * height;
		bot_left_point = position + right_border * height;
		rectangle.setSize(sf::Vector2f(width, height));
		//texture.loadFromFile("D:/Game_Project/Rogalick/bin/map_elements/wall.png");
	}

	void setWallPosition(Vector2 new_position) {
		position = new_position;
		rectangle.setPosition(position.x, position.y);
		rectangle.setTexture(&texture);
		top_right_point = top_border * width + position;
		bot_right_point = top_border * width + position + right_border * height;
		bot_left_point = position + right_border * height;
	}

	void wallRotate(double fi) {
		rectangle.rotate(fi);
		top_border.getRotated(fi);
		bot_border.getRotated(fi);
		left_border.getRotated(fi);
		right_border.getRotated(fi);
		top_right_point = top_border * width + position;
		bot_right_point = top_border * width + position + right_border * height;
		bot_left_point = position + right_border * height;
	}
};

