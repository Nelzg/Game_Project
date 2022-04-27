#include <iostream>
#include <SFML\Graphics.hpp>
#include <cmath>
#include <vector>

struct Vector2 {
    float x;
    float y;

    Vector2(float x_ = 0, float y_ = 0) {
        x = x_;
        y = y_;
    };
    ~Vector2() {
    }
    Vector2 operator+ (const Vector2& other) const {
        struct Vector2 result;
        result.x = x + other.x;
        result.y = y + other.y;
        return result;
    }
    Vector2& operator+= (const Vector2& other) {
        x += other.x;
        y += other.y;
        return *this;
    }
    Vector2 operator- (const Vector2& other) const {
        struct Vector2 result;
        result.x = x - other.x;
        result.y = y - other.y;
        return result;
    }
    Vector2& operator-= (const Vector2& other) {
        x -= other.x;
        y -= other.y;
        return *this;
    }
    float operator* (const Vector2& other) const {
        return x * other.x + y * other.y;
    }
    float operator^ (const Vector2& other) const {
        return x * other.x - y * other.y;
    }
    Vector2 operator* (const float& a) {
        Vector2 result(x * a, y * a);
        return result;
    }
    Vector2 operator/ (const float& a) {
        Vector2 result(x / a, y / a);
        return result;
    }
    Vector2 perpend() {
        Vector2 result(y, -x);
        return result;
    }
    float len() {
        return sqrt(x * x + y * y);
    }
    float squareLen() {
        return x * x + y * y;
    }
    Vector2 norm() {
        Vector2 result(x / sqrt(x * x + y * y), y / sqrt(x * x + y * y));
        return result;
    }

    Vector2 operatorUnarMinus() const {
        Vector2 result(-x, -y);
        return result;
    }
    Vector2& rotate(const char& angle) {
        float tempx = x, tempy = y;
        x = x * cos(angle) - y * sin(angle);
        y = x * sin(angle) + y * cos(angle);
        return *this;
    }
    Vector2 getRotated(const char& angle) {
        Vector2 result(x * cos(angle) - y * sin(angle), x * sin(angle) + y * cos(angle));
        return result;
    }
};

std::ostream& operator<< (std::ostream& stream, const Vector2& v) {
    stream << v.x << " " << v.y;
    return stream;
}

std::istream& operator>> (std::istream& stream, Vector2& v) {
    stream >> v.x >> v.y;
    return stream;
}

class  MaterialPoint
{
public:
    Vector2 position;
    Vector2 velocity;
    Vector2 acceleration;
    float mass;

    MaterialPoint() {

    }
    virtual ~MaterialPoint() {

    }
    virtual void UpdatePosition(float dt) {
        position.x += velocity.x * dt + acceleration.x * dt * dt / 2;
        velocity.x += acceleration.x * dt;
        /*if (position.x < 0 || position.x > 780) {
            velocity.x *= -1;
        }*/
        position.y += velocity.y * dt + acceleration.y * dt * dt / 2;
        velocity.y += acceleration.y * dt;
        /*if (position.y < 0 || position.y > 580) {
            velocity.y *= -1;
        }*/
    }

    Vector2 GetImpulse() const {
        Vector2 a(mass * velocity.x, mass * velocity.y);
        return a;
    }
};

class Particle : public MaterialPoint {
public:
    float radius;
    sf::CircleShape circle;
    int show;
};
class Object {
public :
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
    int ChangeMode(Particle* a, sf::Texture * Modes) {
        if (a->position.x >= position.x - 2 * a->radius && a->position.x <= position.x + 60 && a->position.y >= position.y - 30 && a->position.y <= position.y ) {
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

    void ConnectPortals(Portal *other) {
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

int main()
{
  Spring::loadTexture();
  Lever::loadTexture();
  Portal::loadTexture();
  sf::Texture spring;
  sf::Texture portal;
  sf::Texture Modes[2];
  sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
  std::vector<Particle> particles;
  Spring spr;
  Lever lvr;
  Portal fst;
  Portal snd;
  Object* sprLink = &spr;
  std::string name = "Spring.png";
  if (!spring.loadFromFile(name)) {
      std::cout << "Can't load texture\n";
  }
  spr.sprite.setTexture(spring);
  if (!Modes[0].loadFromFile("Lever_off.png")) {
      std::cout << "Can't load texture\n";
  }
  if (!Modes[1].loadFromFile("Lever_on.png")) {
      std::cout << "Can't load texture\n";
  }
  if (!portal.loadFromFile("Portal.png")) {
      std::cout << "Can't load texture\n";
  }
  lvr.mode = 0;
  spr.mode = lvr.mode;
  lvr.link = sprLink;
  lvr.position = Vector2(300, 400);
  lvr.sprite.setPosition(lvr.position.x, lvr.position.y);
  lvr.sprite.setTexture(Modes[0]);
  //spr.loadTexture("Spring.png");
  spr.position = Vector2(100, 400);
  spr.sprite.setPosition(spr.position.x, spr.position.y);
  fst.position = Vector2(100, 100);
  snd.position = Vector2(400, 100);
  fst.sprite.setPosition(fst.position.x, fst.position.y);
  snd.sprite.setPosition(snd.position.x, snd.position.y);
  fst.sprite.setTexture(portal);
  snd.sprite.setTexture(portal);
  fst.Direction = 1;
  snd.Direction = -1;
  fst.ConnectPortals(&snd);
  std::cout << fst.PositionConnect << " " << snd.PositionConnect << std::endl;
  int p_loc = 0, spr_loc = 1;
  while (window.isOpen())
  {
    window.clear(sf::Color::Red);
    sf::Event event;
    while (window.pollEvent(event)) {
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        if (event.type == sf::Event::Closed)
            window.close();
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            Particle p;
            p.position = Vector2(mousePosition.x, mousePosition.y);
            p.velocity = Vector2(0, 50);
            p.acceleration = Vector2(0, 20);
            p.mass = 1.0f;
            p.radius = 10;
            p.circle.setRadius(p.radius);
            p.circle.setPosition(p.position.x, p.position.y);
            p.circle.setFillColor(sf::Color::Black);
            particles.push_back(p);
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
            Particle q;
            q.position = Vector2(mousePosition.x, mousePosition.y);
            q.velocity = Vector2(50, 0);
            q.acceleration = Vector2(0, 0);
            q.mass = 1.0f;
            q.radius = 10;
            q.circle.setRadius(q.radius);
            q.circle.setPosition(q.position.x, q.position.y);
            q.circle.setFillColor(sf::Color::Black);
            particles.push_back(q);
        }
    }
    if (spr.mode == 1) {
        window.draw(spr.sprite);
    }
    window.draw(lvr.sprite);
    window.draw(fst.sprite);
    window.draw(snd.sprite);
    for (int i = 0; i < particles.size(); i++) {
        particles[i].UpdatePosition(0.01);
        particles[i].circle.setPosition(particles[i].position.x, particles[i].position.y);
        window.draw(particles[i].circle);
        if (spr.mode == 1) {
            spr.GiveImpulse(&particles[i]);
        }
        fst.Teleport(&particles[i]);
        snd.Teleport(&particles[i]);
        if (lvr.ChangeMode(&particles[i], Modes) == 1) {
            particles.erase(particles.begin() + i);
        }
    }
    window.display();

  }

  return 0;
}
