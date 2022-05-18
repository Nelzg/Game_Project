#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include "../../../src/Vector2.h"
#include "MaterialPoint.h"
#include <SFML\Graphics.hpp>
#include "Ball.h"

class Lever : public MaterialPoint {
public:
    sf::CircleShape circle;
    Vector2 position;
    int radius;
    int mode;
    Wall* link;
    static sf::Texture lever;

    Lever(int radius_ = 30) {
        radius = radius_;
        circle.setRadius(radius);
    }

    void setLeverPosition(Vector2 new_position) {
        position = new_position;
        circle.setPosition(position.x, position.y);
    }

    int ChangeMode(Ball& ball, sf::Texture* Modes) {
        if ((position + Vector2(radius, radius) - ball.position).len() <= radius + ball.radius) {
            mode = 1 - mode % 2;
            link->mode = mode;
            circle.setTexture(&Modes[mode]);
            return 1;
        }
        return 0;
    }

};
