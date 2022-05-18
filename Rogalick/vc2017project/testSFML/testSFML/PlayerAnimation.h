#pragma once
#include "../../../3rdparty/SFML-2.4.2/include/SFML/System/Clock.hpp"
#include <SFML\Graphics.hpp>
#include "Mob.h"

#define N 5

class PlayerAnimation: public Mob
{
public:
	PlayerAnimation(float width_, float height_) {
		width = width_;
		height = height_;
		body.setSize(sf::Vector2f(width,height));
	}

	void animation(sf::Clock clock) {
		int t = 1;
		sf::Time time = clock.getElapsedTime();
		int frame_numb = (time.asMilliseconds() / 200) % N;
		switch (frame_numb) 
		{
		case 0: {
			texture.loadFromFile("hero_animation/hero_1.png");
			break;
			}
		case 1: {
			texture.loadFromFile("hero_animation/hero_2.png");
			break;
		}
		case 2: {
			texture.loadFromFile("hero_animation/hero_3.png");
			break;
		}
		case 3: {
			texture.loadFromFile("hero_animation/hero_4.png");
			break;
		}
		case 4: {
			texture.loadFromFile("hero_animation/hero_1.png");
			break;
		}
		default:
			texture.loadFromFile("hero_animation/hero_1.png");
		}
		body.setTexture(&texture);

		int prevX = body.getPosition().x;
		int prevY = body.getPosition().y;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			position.x = position.x - walking_velocity.x * t;
			mobSetPosition(position);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			position.x = position.x + walking_velocity.x * t;
			mobSetPosition(position);
			
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)&&(!in_air))
		{
			velocity = Vector2(0, -10);
			acceleration = Vector2(0, 0.2);
			in_air = 1;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			position.y = position.y + 1 * t;
			mobSetPosition(position);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			position.y = position.y - 1 * t;
			mobSetPosition(position);
		}
		if (in_air == 1) {
			acceleration = Vector2(0, 0.2);
			position.y = position.y + velocity.y * t;
			mobSetPosition(position);
			velocity.y = velocity.y + acceleration.y * t;
		}
		else {
			velocity.y = 0;
			acceleration.y = 0;
		}
		if (velocity.y >= 10) {
			velocity.y = 10;
		}
	}
};

