#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include "../../../src/Vector2.h"
#include "MaterialPoint.h"
#include <SFML\Graphics.hpp>
#include "Ball.h"
#include "PlayerAnimation.h"

class Portal : public MaterialPoint {
public:
    int id;
    Vector2 PositionConnect;
    sf::CircleShape circle;
    int radius;
    sf::Texture texture;

    Portal(int numb, int radius_ = 30) {
        radius = radius_;
        circle.setRadius(radius);
        if (numb == 1) {
            texture.loadFromFile("D:/Game_Project/Rogalick/bin/map_elements/portal_1.png");
        }
        else {
            texture.loadFromFile("D:/Game_Project/Rogalick/bin/map_elements/portal_2.png");
        }
    }

    void setPortalPosition(Vector2 new_position) {
        position = new_position;
        circle.setPosition(position.x, position.y);
        circle.setTexture(&texture);
    }

    void ConnectPortals(Portal& other) {
        PositionConnect.x = other.position.x;
        PositionConnect.y = other.position.y;
        other.PositionConnect.x = position.x;
        other.PositionConnect.y = position.y;
        
    }

    void Teleport(Ball& ball) {
        if ((position + Vector2(radius,radius) - ball.position).len() < radius) {
            ball.velocity = Vector2(1, 0) * ball.velocity.len();
            ball.setBallPosition(Vector2(PositionConnect.x + ball.radius + radius * 2 + 1, PositionConnect.y + radius));
        }
    }

    void TeleportHero(PlayerAnimation& a) {
        if (!(a.position.x + a.width < position.x) && !(a.position.x > position.x + radius * 2) && !(a.position.y + a.height < position.y) && !(a.position.y > position.y + 2 * radius)) {
            a.velocity = Vector2(1, 0) * a.velocity.len();
            a.mobSetPosition(Vector2(PositionConnect.x + a.width + radius *2 + 1, PositionConnect.y + radius));
        }
    }
};
