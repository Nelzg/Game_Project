#include <SFML\Graphics.hpp>
#include <math.h>
#include "Vector2.h"
#include <vector>
#include "../vc2017project/testSFML/testSFML/Ball.h"
#include "../vc2017project/testSFML/testSFML/LaserBeam.h"
#include "../vc2017project/testSFML/testSFML/PlayerAnimation.h"
#include "../vc2017project/testSFML/testSFML/Wall.h"
#include "../vc2017project/testSFML/testSFML/Collision.h"

#define speed 1
#define dt 0.2f
#define screen_height 1000
#define screen_width 1000

int main()
{
  std::vector<Ball> particles;
  std::vector<LaserBeam> lasers;
  std::vector <Wall> walls;

  sf::RectangleShape player2;
  int count1;
  int count2 = 1;
  sf::RenderWindow window(sf::VideoMode(screen_height, screen_width), "My window");
  sf::Clock clock;
  PlayerAnimation player;
  sf::Time time_begin_1 = clock.getElapsedTime();
  sf::Time time_begin_2= clock.getElapsedTime();
  sf::Time time_begin_3 = clock.getElapsedTime();
  sf::Time time_begin_4 = clock.getElapsedTime();
  player.height = 20;
  player.width = 20;
  sf::CircleShape circle;
  circle.setRadius(10);
  circle.setFillColor(sf::Color::Black);
  Wall wall(200, 100);
  Ball p(10);
  int count = 0;

  while (window.isOpen())
  {

    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
    }
    window.clear(sf::Color::Red);
    sf::Time time_count = clock.getElapsedTime();

    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::W) == 0) && (sf::Mouse::isButtonPressed(sf::Mouse::Left) == 0) && (count == 1)) {
        count = 0;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && sf::Mouse::isButtonPressed(sf::Mouse::Left) && (count == 0)) {
        
        time_begin_4 = time_count;
        wall.setWallPosition(Vector2(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y));
        
        walls.push_back(wall);
        count = 1;
    }



    if ((sf::Mouse::isButtonPressed(sf::Mouse::Left)) && ((time_count - time_begin_1).asSeconds() >= dt) && (sf::Keyboard::isKeyPressed(sf::Keyboard::W) == 0)) {
        p.mass = 1.0f;
        p.radius = 10;
        time_begin_1 = time_count;
        Vector2 mouse_pos = Vector2(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
        p.velocity = Vector2(mouse_pos.x - player.body.getPosition().x, mouse_pos.y - player.body.getPosition().y).norm() * speed;
        p.position = Vector2(player.position.x, player.position.y);
        particles.push_back(p);
    }
    
    
    if ((sf::Mouse::isButtonPressed(sf::Mouse::Right)) && ((time_count - time_begin_2).asSeconds() >= dt)) {
        LaserBeam l;
        time_begin_2 = time_count;
        l.mass = 1.0f;
        l.rectangle.setSize(sf::Vector2f(20, 1));
        Vector2 mouse_pos = Vector2(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
        l.velocity = Vector2(mouse_pos.x - player.body.getPosition().x, mouse_pos.y - player.body.getPosition().y).norm() * speed;
        l.position = Vector2(player.position.x, player.position.y);
        
        if ((mouse_pos.y - l.position.y) >= 0) {
            l.rectangle.rotate(180 + acos((Vector2(1, 0) * l.velocity) / l.velocity.len()) * 180 / M_PI);
        }
        else {
            l.rectangle.rotate(180-acos((Vector2(1, 0) * l.velocity) / l.velocity.len()) * 180 / M_PI);
        }
        l.rectangle.setFillColor(sf::Color::Black);
        
        lasers.push_back(l);
    }

    if ((time_count - time_begin_3).asSeconds() >= dt) {
        time_count = time_begin_3;
        for (int i = 0; i < lasers.size(); i++) {
            lasers[i].UpdatePosition(1);
            lasers[i].rectangle.setPosition(lasers[i].position.x, lasers[i].position.y);
            window.draw(lasers[i].rectangle);
            if ((screen_height < lasers[i].position.x) || (lasers[i].position.x < 0) || (lasers[i].position.y < 0) || (lasers[i].position.y > screen_width)) {
                lasers.erase(lasers.begin() + i);
            }
        }

        for (int i = 0; i < particles.size(); i++) {
            particles[i].UpdatePosition(1);
            particles[i].circle.setPosition(particles[i].position.x, particles[i].position.y);
            window.draw(particles[i].circle);
            if ((screen_width < particles[i].position.x) || (particles[i].position.x < 0) || (particles[i].position.y < 0) || (particles[i].position.y > screen_height)) {
                particles.erase(particles.begin() + i);
            }
            for (int j = 0; j < walls.size(); j++) {
                Vector2 prev_pos = particles[i].position;
                if (Collision::collisionOfBallWithRect(walls[j].rectangle, &(particles[i]))) {
                    particles[i].position = prev_pos;
                }
                window.draw(walls[j].rectangle);
            }
        }
        player.animation(clock);
        window.draw(player.body);
    }
    
    for (int i = 0; i < walls.size(); i++) {
        window.draw(walls[i].rectangle);
    }

    //if (walls.size() > 0) {
      //  circle.setOrigin(circle.getRadius(), circle.getRadius());
       // circle.setPosition(walls[0].rectangle.getPosition().x, walls[0].rectangle.getPosition().y);
      //  window.draw(circle);
   // }

    window.display();
  }


  return 0;
}