#pragma once
#include <SFML\Graphics.hpp>
#include "Ball.h"
#include "Mob.h"
#include "Wall.h"

class Collisions
{
public:
	static bool collisionOfBallWithRect(sf::RectangleShape rect, Ball *ball) {
		Vector2 pos = Vector2(rect.getPosition().x, rect.getPosition().y);
		Vector2 a(1, 0), b(1, 0), c;
		Vector2 size = Vector2(rect.getSize().x, rect.getSize().y);
		Vector2 prev_pos = (* ball).position;
		float rotation_a;
		int count = 0;
		a.getRotated(rect.getRotation());
		rotation_a = rect.getRotation();

		if (collisionOfBallWithline(pos, pos + Vector2(size.x, 0).rotate(rotation_a), *ball)) {
			c = Vector2(size.x, 0).rotate(rotation_a + 270).norm();
			(*ball).velocity = -(*ball).velocity;
			if ((*ball).velocity.rotate((acos((*ball).velocity.norm() * c) * 180 / M_PI)).norm() == c) {
				(*ball).velocity = (*ball).velocity.rotate(2 * (acos((*ball).velocity.norm() * c) * 180 / M_PI));
			}
			else {
				(*ball).velocity = (*ball).velocity.rotate((- 2) * (acos((*ball).velocity.norm() * c) * 180 / M_PI));
			}
			(*ball).position = prev_pos;
			count++;
		}
			
		if (collisionOfBallWithline(pos, pos + Vector2(0, size.y).rotate(rotation_a), *ball)) {
			c = Vector2(0, size.y).rotate(rotation_a + 90).norm();
			(*ball).velocity = -(*ball).velocity;
			if ((*ball).velocity.rotate((acos((*ball).velocity.norm() * c) * 180 / M_PI)).norm() == c) {
				(*ball).velocity = (*ball).velocity.rotate(2 * (acos((*ball).velocity.norm() * c) * 180 / M_PI));
			}
			else {
				(*ball).velocity = (*ball).velocity.rotate( - 2 * (acos((*ball).velocity.norm() * c) * 180 / M_PI));
			}
			
			(*ball).position = prev_pos;
			count++;;
		}

		if (collisionOfBallWithline(pos + Vector2(0, size.y).rotate(rotation_a), pos + Vector2(0, size.y).rotate(rotation_a) + Vector2(size.x, 0).rotate(rotation_a), *ball)) {
			c = Vector2(size.x, 0).rotate(rotation_a + 270).norm();
			(*ball).velocity = -(*ball).velocity;
			if ((*ball).velocity.rotate((acos((*ball).velocity.norm() * c) * 180 / M_PI)).norm() == c) {
				(*ball).velocity = (*ball).velocity.rotate(2 * (acos((*ball).velocity.norm() * c) * 180 / M_PI));
				//std::cout << (*ball).velocity.rotate((acos((*ball).velocity.norm() * c) * 180 / M_PI)).norm().x << " " << (*ball).velocity.rotate((acos((*ball).velocity.norm() * c) * 180 / M_PI)).norm().y << "\n";
			}
			else {
				(*ball).velocity = (*ball).velocity.rotate(-2 * (acos((*ball).velocity.norm() * c) * 180 / M_PI));
			}
			//std::cout << (acos((*ball).velocity.norm() * c) * 180 / M_PI) << "\n";
			(*ball).position = prev_pos;
			count++;;
		}

		if (collisionOfBallWithline(pos + Vector2(size.x, 0).rotate(rotation_a), pos + Vector2(size.x, 0).rotate(rotation_a) + Vector2(0, size.y).rotate(rotation_a), *ball)) {
			c = Vector2(0, size.y).rotate(rotation_a + 90).norm();
			(*ball).velocity = -(*ball).velocity;
			if ((*ball).velocity.rotate((acos((*ball).velocity.norm() * c) * 180 / M_PI)).norm() == c) {
				(*ball).velocity = (*ball).velocity.rotate(2 * (acos((*ball).velocity.norm() * c) * 180 / M_PI));
			}
			else {
				(*ball).velocity = (*ball).velocity.rotate( - 2 * (acos((*ball).velocity.norm() * c) * 180 / M_PI));
			}
			
			(*ball).position = prev_pos;
			count++;
		}

		if (count == 0) {
			return 0;
		}
		else {
			return 1;
		}
	}


	static bool collisionOfBallWithline(Vector2 pos_begin, Vector2 pos_end, Ball ball) {
		float c, d, e, t1, t2;
		Vector2 a = (pos_end - pos_begin).norm();
		e = (pos_begin.x - ball.position.x) * (pos_begin.x - ball.position.x) + (pos_begin.y - ball.position.y) * (pos_begin.y - ball.position.y) - ball.radius * ball.radius;
		d = ((pos_begin.x - ball.position.x) * a.x + a.y * (pos_begin.y - ball.position.y));
		c = (a.x * a.x + a.y * a.y);
		if (d * d - c * e >= 0) {
			t1 = (-d - sqrt(d * d - c * e)) / c;
			t2 = (-d + sqrt(d * d - c * e)) / c;
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


	




	static bool collisionOfBallWithWall(Wall wall, Ball& ball) {
		int count = 0;
		if (collisionOfBallWithWallSide(ball,wall.top_border, wall.position,wall.width)) {
			ball.velocity =  ball.velocity - wall.left_border * (wall.left_border * ball.velocity) * 2;
			count++;
		}
		if (collisionOfBallWithWallSide(ball, wall.right_border, wall.top_right_point, wall.height)) {
			ball.velocity = ball.velocity - wall.top_border * (wall.top_border * ball.velocity) * 2;
			count++;
		}
		if (collisionOfBallWithWallSide(ball, wall.bot_border, wall.bot_right_point, wall.width)) {
			ball.velocity = ball.velocity - wall.right_border * (wall.right_border * ball.velocity) * 2;
			count++;
		}
		if (collisionOfBallWithWallSide(ball, wall.left_border, wall.bot_left_point, wall.height)) {
			ball.velocity = ball.velocity - wall.bot_border * (wall.bot_border * ball.velocity) * 2;
			count++;
		}

		if (count == 0) {
			return 0;
		}
		else {
			return 1;
		}
	}

	static bool collisionOfBallWithWallSide(Ball ball, Vector2 side, Vector2 side_point, int side_length) {
		float b, c, t1, t2;
		b = ((ball.position - side_point) * side);
		c = (ball.position - side_point) * (ball.position - side_point) - ball.radius * ball.radius;
		if ((b * b - c) >= 0) {
			t1 = (b - sqrt(b * b - c));
			t2 = (b + sqrt(b * b - c));
			std::cout << t1 << " " << t2 << "\n";
			if (((t1 >= 0) && (t1 <= side_length)) || ((t2 >= 0) && (t2 <= side_length))) {
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

