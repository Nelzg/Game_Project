#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include "../../../src/Vector2.h"
#include "MaterialPoint.h"
#include <SFML\Graphics.hpp>
#include "Ball.h"

class Lever : public MaterialPoint {
public:
    sf::RectangleShape rectangle;
    Vector2 position;
    int mode;
    //Object* link;
    static sf::Texture lever;

    static void loadTexture() {
        if (!lever.loadFromFile("Spring.png")) {
            std::cout << "Can't load texture\n";
        }
        std::cout << "All done" << std::endl;
    }

    int ChangeMode(Ball* a, sf::Texture* Modes) {
        if (a->position.x >= position.x - 2 * a->radius && a->position.x <= position.x + 60 && a->position.y >= position.y - 30 && a->position.y <= position.y) {
            mode = 1 - mode % 2;
            //link->mode = mode;
            rectangle.setTexture(&Modes[mode]);
            return 1;
        }
        return 0;
    }

};
