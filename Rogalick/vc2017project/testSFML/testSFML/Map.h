#pragma once
#include <SFML\Graphics.hpp>

class Map
{
	std::vector<sf::RectangleShape> map;

	void loadMap(sf::RenderWindow &window) {
		window.draw(map[1]);
	}

	void loadMapStructures() {
		sf::RectangleShape rectangle;
	}
};

