#include <SFML\Graphics.hpp>
#include <math.h>
#include "Vector2.h"
#include <vector>
#include "../vc2017project/testSFML/testSFML/Ball.h"
#include "../vc2017project/testSFML/testSFML/LaserBeam.h"
#include "../vc2017project/testSFML/testSFML/PlayerAnimation.h"
#include "../vc2017project/testSFML/testSFML/Wall.h"
#include "../vc2017project/testSFML/testSFML/Collisions.h"
#include "../vc2017project/testSFML/testSFML/Portal.h"
#include "../vc2017project/testSFML/testSFML/Lever.h"

#define speed 1
#define dt 0.2f
#define frames 60.0f
#define dt_mob 1.0f
#define screen_height 1000
#define screen_width 1000

int main()
{
  std::vector<Ball> particles;
  std::vector<Ball> particles_enemy;
  std::vector<LaserBeam> lasers;
  std::vector <Wall> walls;
  std::vector<Mob> enemies;
  std::vector <Wall> walls_without_collisions;

  sf::RectangleShape player2;
  int count1;
  int count2 = 1;
  sf::RenderWindow window(sf::VideoMode(screen_height, screen_width), "My window");
  sf::Clock clock;
  PlayerAnimation player(20,20);
  sf::Time time_begin_1 = clock.getElapsedTime();
  sf::Time time_begin_2= clock.getElapsedTime();
  sf::Time time_begin_3 = clock.getElapsedTime();
  sf::Time time_begin_4 = clock.getElapsedTime();
  sf::Time time_begin_enemy = clock.getElapsedTime();
  sf::Time time_begin_frame = clock.getElapsedTime();
  
  player.health = 100;

  sf::Time time_begin_animation = clock.getElapsedTime();
  
  sf::CircleShape circle;
  circle.setRadius(10);
  circle.setFillColor(sf::Color::Black);
  player.acceleration = Vector2(0, 0.8);
  player.mobSetPosition(Vector2(15, 15));
  Wall wall(200, 100);
  Wall wall2(200, 100);
  wall2.setWallPosition(Vector2(500, 500));
  Ball p(10);
  int count = 0;

  Mob enemy;
  enemy.height = 20;
  enemy.width = 20;
  enemy.body.setPosition(700, 700);
  enemy.body.setOrigin(enemy.width / 2, enemy.height / 2);
  enemy.body.setSize(sf::Vector2f(enemy.width, enemy.height));
  enemy.texture.loadFromFile("hero_animation/hero_3.png");
  enemy.body.setTexture(&enemy.texture);
  enemies.push_back(enemy);

  Portal portal_one(1,30);
  Portal portal_two(2,30);
  portal_one.setPortalPosition(Vector2(50,50));
  portal_two.setPortalPosition(Vector2(800, 830));
  portal_one.ConnectPortals(portal_two);
  sf::Texture Modes[2];
  if (!Modes[1].loadFromFile("D:/Game_Project/Rogalick/bin/map_elements/lever_off.png")) {
      std::cout << "Can't load texture\n";
  }
  if (!Modes[0].loadFromFile("D:/Game_Project/Rogalick/bin/map_elements/lever_on.png")) {
      std::cout << "Can't load texture\n";
  }
  Lever lvr;
  lvr.mode = 1;
  wall2.mode = lvr.mode;
  lvr.link = &wall2;
  
  lvr.setLeverPosition(Vector2(270, 500));
  lvr.circle.setTexture(&Modes[1]);

  sf::Texture map_texture;
  map_texture.loadFromFile("D:/Game_Project/Rogalick/bin/map_elements/background.png");
  map_texture.setSmooth(true);
  sf::Sprite background;
  background.setTexture(map_texture);
  
  while (window.isOpen()) {

      sf::Event event;
      while (window.pollEvent(event)) {
          if (event.type == sf::Event::Closed)
              window.close();
      }
      sf::Time time_count = clock.getElapsedTime();

      window.clear();
      window.draw(background);

      if ((sf::Keyboard::isKeyPressed(sf::Keyboard::W) == 0) && (sf::Mouse::isButtonPressed(sf::Mouse::Left) == 0) && (count == 1)) {
          count = 0;
      }

      if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && sf::Mouse::isButtonPressed(sf::Mouse::Left) && (count == 0)) {
          time_begin_4 = time_count;
          wall.width = 100;
          wall.height = 20;
          wall.rectangle.setSize(sf::Vector2f(wall.width, wall.height));
          wall.setWallPosition(Vector2(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y));
          while (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
              wall.rectangle.rotate(1);
              window.draw(wall.rectangle);
          }
          walls.push_back(wall);
          count = 1;
      }

      if (walls_without_collisions.size() == 0) {
          wall.width = screen_width;
          wall.height = 400;
          wall.rectangle.setSize(sf::Vector2f(wall.width, wall.height));
          wall.setWallPosition(Vector2(0, 900));
          walls_without_collisions.push_back(wall);

          wall.width = 200;
          wall.height = screen_height;
          wall.rectangle.setSize(sf::Vector2f(wall.width, wall.height));
          wall.setWallPosition(Vector2(-190, 0));
          walls_without_collisions.push_back(wall);

          wall.width = 200;
          wall.height = screen_height;
          wall.rectangle.setSize(sf::Vector2f(wall.width, wall.height));
          wall.setWallPosition(Vector2(screen_width - 10, 0));
          walls_without_collisions.push_back(wall);

          wall.width = 200;
          wall.height = 100;
          wall.rectangle.setSize(sf::Vector2f(wall.width, wall.height));
          wall.setWallPosition(Vector2(40, 120));
          walls_without_collisions.push_back(wall);

          wall.width = 300;
          wall.height = 100;
          wall.rectangle.setSize(sf::Vector2f(wall.width, wall.height));
          wall.setWallPosition(Vector2(100, 400));
          walls_without_collisions.push_back(wall);

          wall.width = 200;
          wall.height = 100;
          wall.rectangle.setSize(sf::Vector2f(wall.width, wall.height));
          wall.setWallPosition(Vector2(750, 720));
          walls_without_collisions.push_back(wall);
          walls_without_collisions.push_back(wall2);
          lvr.link = &walls_without_collisions[6];

          

      }

      if (walls.size() == 0) {
          wall.width = 50;
          wall.height = 200;
          wall.rectangle.setSize(sf::Vector2f(wall.width, wall.height));
          wall.setWallPosition(Vector2(100, 500));
          walls.push_back(wall);

          wall.width = 200;
          wall.height = 50;
          wall.rectangle.setSize(sf::Vector2f(wall.width, wall.height));
          wall.setWallPosition(Vector2(150, 450));
          walls.push_back(wall);

          wall.width = 50;
          wall.height = 200;
          wall.rectangle.setSize(sf::Vector2f(wall.width, wall.height));
          wall.setWallPosition(Vector2(350, 500));
          walls.push_back(wall);

          wall.width = 200;
          wall.height = 50;
          wall.rectangle.setSize(sf::Vector2f(wall.width, wall.height));
          wall.setWallPosition(Vector2(200, 700));
          walls.push_back(wall);

      }

      if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && sf::Mouse::isButtonPressed(sf::Mouse::Right) && (count == 0)) {
          time_begin_4 = time_count;
          wall.rectangle.setSize(sf::Vector2f(200, 100));
          wall.width = 200;
          wall.height = 100;
          wall.setWallPosition(Vector2(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y));
          while (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
              wall.rectangle.rotate(1);
              window.draw(wall.rectangle);
          }
          walls_without_collisions.push_back(wall);
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
              l.rectangle.rotate(180 - acos((Vector2(1, 0) * l.velocity) / l.velocity.len()) * 180 / M_PI);
          }
          l.rectangle.setFillColor(sf::Color::Black);
          lasers.push_back(l);
      }



      for (int i = 0; i < enemies.size(); i++) {
          window.draw(enemies[i].body);
          if ((player.body.getPosition().y <= enemies[i].body.getPosition().y + enemies[i].height) && (player.body.getPosition().y + player.body.getSize().y / 2 >= enemies[i].body.getPosition().y) && ((time_count - time_begin_enemy).asSeconds() >= dt_mob)) {
              int Right = 1;
              time_begin_enemy = time_count;
              for (int j = 0; j < walls.size(); j++) {
                  if ((enemies[i].body.getPosition().y + 20 > walls[j].rectangle.getPosition().y) && (enemies[i].body.getPosition().y < walls[j].rectangle.getPosition().y + walls[j].rectangle.getSize().y) && ((enemies[i].body.getPosition().x - player.position.x) * (enemies[i].body.getPosition().x - walls[j].rectangle.getPosition().x) > 0)) {
                      Right = 0;
                  }
              }
              if (Right == 1) {
                  p.mass = 1.0f;
                  p.radius = 10;
                  p.damage = 20;
                  p.velocity = Vector2(player.body.getPosition().x - enemies[i].body.getPosition().x, 0).norm() * speed;
                  p.position = Vector2(enemies[i].body.getPosition().x, enemies[i].body.getPosition().y);
                  particles_enemy.push_back(p);
              }
          }
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

          int n = 0;
          for (int i = 0; i < particles_enemy.size(); i++) {
              particles_enemy[i].UpdatePosition(1);
              if ((particles_enemy[i].position.x + 2 * particles_enemy[i].radius >= player.position.x) && (particles_enemy[i].position.x <= player.position.x + player.body.getSize().x / 2) && (particles_enemy[i].position.y + 2 * particles_enemy[i].radius >= player.position.y) && (particles_enemy[i].position.y <= player.body.getPosition().y + player.body.getSize().y / 2)) {
                  player.health -= particles_enemy[i].damage;
                  particles_enemy.erase(particles_enemy.begin() + i);
              }
              else {
                  particles_enemy[i].circle.setPosition(particles_enemy[i].position.x, particles_enemy[i].position.y);
                  window.draw(particles_enemy[i].circle);
                  if ((screen_width < particles_enemy[i].position.x) || (particles_enemy[i].position.x < 0) || (particles_enemy[i].position.y < 0) || (particles_enemy[i].position.y > screen_height)) {
                      particles_enemy.erase(particles_enemy.begin() + i);
                  }

                  for (int j = 0; j < walls.size(); j++) {
                      Vector2 prev_pos = particles_enemy[i].position;
                      if (Collisions::collisionOfBallWithRect(walls[j].rectangle, &(particles_enemy[i]))) {
                          particles_enemy.erase(particles_enemy.begin() + i);
                          n++;
                      }

                  }

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
                  if (Collisions::collisionOfBallWithWall(walls[j], particles[i])) {
                      particles[i].position = prev_pos;
                  }

              }
              portal_one.Teleport(particles[i]);
              int nu = -1;
              for (int j = 0; j < walls_without_collisions.size(); j++) {
                  if (walls_without_collisions[j].mode != 1) {
                      if (Collisions::collisionOfBallWithWall(walls_without_collisions[j], particles[i])) {
                          nu = i;
                      }
                  }
              }
              if (nu != -1) {
                  particles.erase(particles.begin() + nu);
              }
              int ku = -1;
              if (lvr.ChangeMode(particles[i], Modes)) {
                  ku = i;
                  
              }
              if (ku != -1) {
                  particles.erase(particles.begin() + ku);
              }
              portal_two.Teleport(particles[i]);
          }
          portal_one.TeleportHero(player);
          portal_two.TeleportHero(player);
          player.animation(clock);
          window.draw(player.body);
      }

    window.draw(lvr.circle);

    int count3 = walls_without_collisions.size();
    for (int i = 0; i < walls_without_collisions.size(); i++) {
        if (walls_without_collisions[i].mode == 1) {
            count3--;
        }
        else {
            if (!player.checkIfInAir(walls_without_collisions[i])) {
            }
            else {
                count3--;
            }

            

            if ((walls_without_collisions[i].position.x - player.position.x - player.width < 0) && !(player.position.y > walls_without_collisions[i].position.y + walls_without_collisions[i].height - walls_without_collisions[i].height / 15) && !(player.position.y + player.height < walls_without_collisions[i].position.y + walls_without_collisions[i].height / 15) && (player.position.x < walls_without_collisions[i].position.x + walls_without_collisions[i].width / 2)) {
                player.position.x = walls_without_collisions[i].position.x - player.width;
            }
            if ((player.position.x - walls_without_collisions[i].position.x - walls_without_collisions[i].width < 0) && !(player.position.y > walls_without_collisions[i].position.y + walls_without_collisions[i].height - walls_without_collisions[i].height / 15) && !(player.position.y + player.height < walls_without_collisions[i].position.y + walls_without_collisions[i].height / 15) && (player.position.x > walls_without_collisions[i].position.x + walls_without_collisions[i].width / 2)) {
                player.position.x = walls_without_collisions[i].position.x + walls_without_collisions[i].width;
            }
        }
        if (count3 == 0) {
                player.in_air = 1;
        }
    }

    
   

    

    for (int i = 0; i < walls.size(); i++) {
        window.draw(walls[i].rectangle);
    }

    for (int i = 0; i < walls_without_collisions.size(); i++) {
        if (walls_without_collisions[i].mode == 0) {
            window.draw(walls_without_collisions[i].rectangle);
        }
    }
    window.draw(portal_one.circle);
    window.draw(portal_two.circle);
    
    
    
    window.display();
      
  }


  return 0;
}
