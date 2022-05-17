#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include "../../../src/Vector2.h"
#include "MaterialPoint.h"
#include <SFML\Graphics.hpp>
#include "Ball.h"

class Portal : public MaterialPoint {
public:
    int id;
    Vector2 PositionConnect;
    int Direction;
    int mode;
    static sf::Texture portal;

    static void loadTexture() {
        if (!portal.loadFromFile("Spring.png")) {
            std::cout << "Can't load texture\n";
        }
        std::cout << "All done" << std::endl;
    }

    void ConnectPortals(Portal& other) {
        PositionConnect.x = other.position.x;
        PositionConnect.y = other.position.y;
        other.PositionConnect.x = position.x;
        other.PositionConnect.y = position.y;
        mode = 1;
        other.mode = 1;
    }

    void Teleport(Ball& ball) {
        if (ball.position.x > PositionConnect.x - 2 * ball.radius && ball.position.x < PositionConnect.x + 30 && ball.position.y > PositionConnect.y - 60 && ball.position.y < PositionConnect.y) {
            if (Direction == 1) {
                ball.position.x = position.x + 30;
            }
            else {
                ball.position.x = position.x - 2 * ball.radius;
            }
            ball.position.y = position.y;
            ball.circle.setPosition(ball.position.x, ball.position.y);
            ball.velocity.x = Direction * abs(ball.velocity.x);
            std::cout << position << " " << PositionConnect << " " << ball.position << std::endl;
            ball.acceleration.x = Direction * abs(ball.acceleration.x);
        }
    }
};
