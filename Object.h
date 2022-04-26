#pragma once
#include <Particle.h>
class Object {
public:
    sf::Sprite sprite;
    Vector2 position;
    int mode;
    Object() {}
    ~Object() {}
};

class Spring : public Object {
public:
    static sf::Texture spring;
    static void loadTexture() {
        if (!spring.loadFromFile("Spring.png")) {
            std::cout << "Can't load texture\n";
        }
        std::cout << "All done" << std::endl;
    }
    Spring() {
        mode = 1;
        sprite.setTexture(spring);
    }
    void GiveImpulse(Particle* a) {
        if (position.y <= a->position.y + 2 * a->radius && a->position.x > position.x - 60 && a->position.x < position.x + 60 && a->velocity.y > 0 && a->position.y <= position.y + 30) {
            a->velocity.y = -80;
            std::cout << "Impulse given" << std::endl;
        }
        if (a->position.x > position.x - 2 * a->radius && a->position.x < position.x + 60 && a->velocity.y <= 0 && a->position.y >= position.y - 30 && a->position.y <= position.y + 30) {
            a->position.x -= 0.01 * a->velocity.x + 0.01 * 0.01 * a->acceleration.x;
            a->velocity.x = 0;
            a->acceleration.x = 0;
        }
    }
};

class Lever : public Object {
public:
    int mode;
    Object* link;
    static sf::Texture lever;
    static void loadTexture() {
        if (!lever.loadFromFile("Spring.png")) {
            std::cout << "Can't load texture\n";
        }
        std::cout << "All done" << std::endl;
    }
    int ChangeMode(Particle* a, sf::Texture* Modes) {
        if (a->position.x >= position.x - 2 * a->radius && a->position.x <= position.x + 60 && a->position.y >= position.y - 30 && a->position.y <= position.y) {
            mode = 1 - mode % 2;
            link->mode = mode;
            sprite.setTexture(Modes[mode]);
            return 1;
        }
        return 0;
    }

};

class Portal : public Object {
public:
    int id;
    Vector2 PositionConnect;
    int Direction;
    static sf::Texture portal;
    static void loadTexture() {
        if (!portal.loadFromFile("Spring.png")) {
            std::cout << "Can't load texture\n";
        }
        std::cout << "All done" << std::endl;
    }

    void ConnectPortals(Portal* other) {
        PositionConnect.x = other->position.x;
        PositionConnect.y = other->position.y;
        other->PositionConnect.x = position.x;
        other->PositionConnect.y = position.y;
        mode = 1;
        other->mode = 1;
    }
    void Teleport(Particle* a) {
        if (a->position.x > PositionConnect.x - 2 * a->radius && a->position.x < PositionConnect.x + 30 && a->position.y > PositionConnect.y - 60 && a->position.y < PositionConnect.y) {
            if (Direction == 1) {
                a->position.x = position.x + 30;
            }
            else {
                a->position.x = position.x - 2 * a->radius;
            }
            a->position.y = position.y;
            a->circle.setPosition(a->position.x, a->position.y);
            a->velocity.x = Direction * abs(a->velocity.x);
            std::cout << position << " " << PositionConnect << " " << a->position << std::endl;
            a->acceleration.x = Direction * abs(a->acceleration.x);
        }
    }
};
