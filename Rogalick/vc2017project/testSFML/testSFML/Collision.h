#pragma once
#include <SFML\Graphics.hpp>
#include "Ball.h"

class Collision
{
public:
	static bool collisionWithRect(sf::RectangleShape rect, Ball ball) {
		Vector2 pos = Vector2(rect.getPosition().x, rect.getPosition().y);
		Vector2 a(1, 0), b(1, 0);
		Vector2 size = Vector2(rect.getSize().x, rect.getSize().y);
		float c, d, e, t1, t2, rotation_a;
		a.getRotated(rect.getRotation());
		rotation_a = rect.getRotation();
		
		//std::cout << Vector2(size.x, 0).rotate(rotation_a).x << " " << Vector2(size.x, 0).rotate(rotation_a).y << "\n";
		//std::cout << Vector2(0, size.y).rotate(rotation_a).x << " " << Vector2(0, size.y).rotate(rotation_a).y << "\n";
		if (collisionWithline(pos, pos + Vector2(size.x, 0).rotate(rotation_a), ball) || collisionWithline(pos, pos + Vector2(0, size.y).rotate(rotation_a), ball) ||
			collisionWithline(pos + Vector2(0, size.y).rotate(rotation_a), pos + Vector2(0, size.y).rotate(rotation_a) + Vector2(size.x, 0).rotate(rotation_a), ball) || collisionWithline(pos + Vector2(size.x, 0).rotate(rotation_a), pos + Vector2(size.x, 0).rotate(rotation_a) + Vector2(0, size.y).rotate(rotation_a), ball)) {
			return 1;
		}
		else {
			return 0;
		}
	}

	static bool collisionWithline(Vector2 pos_begin, Vector2 pos_end, Ball ball) {
		float c, d, e, t1, t2;
		Vector2 a = (pos_end-pos_begin).norm();
		e = (pos_begin.x - ball.position.x) * (pos_begin.x - ball.position.x) + (pos_begin.y - ball.position.y) * (pos_begin.y - ball.position.y) - ball.radius * ball.radius;
		d = ((pos_begin.x - ball.position.x) * a.x + a.y * (pos_begin.y - ball.position.y));
		c = (a.x * a.x + a.y * a.y);
		if (d * d - c * e >= 0) {
			t1 = (-d - sqrt(d * d - c * e)) / c;
			t2 = (-d + sqrt(d * d - c * e)) / c;
			std::cout << t1 << " " << t2 << "\n";
			
			if ((((pos_end - pos_begin).len() >= t1) && (t1 >= 0)) || (((pos_end - pos_begin).len() >= t2) && (t2 >= 0))) {
				return 1;
			}
			else {
				return 0;
			}
		}
		else {
			return 0;
		}
	}
};

