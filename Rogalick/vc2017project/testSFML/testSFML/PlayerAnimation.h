#pragma once
#include "../../../3rdparty/SFML-2.4.2/include/SFML/System/Clock.hpp"
#include <SFML\Graphics.hpp>
#include "Mob.h"

#define N 5

class PlayerAnimation: public Mob
{
public:
	
	PlayerAnimation() {
		body.setOrigin(width/2,height/2);
		body.setSize(sf::Vector2f(width,height));
	}

	void animation(sf::Clock clock) {
		int t = 2;
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

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			body.move(-1 * t, 0);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			body.move(1 * t, 0);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			body.move(0, -1 * t);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			body.move(0, 1 * t);
		}
		if ((body.getPosition().x > 900) || (body.getPosition().x < 0) || (body.getPosition().y > 500) || (body.getPosition().y < 0)) {
			body.setPosition(prevX, prevY);
		}
		position.x = body.getPosition().x;
		position.y = body.getPosition().y;
	}
};

