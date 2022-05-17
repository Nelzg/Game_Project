#pragma once
#ifndef COLLISION_H
#define COLLISION_H

class Collision
{
public:
	static bool collisionOfBallWithRect(sf::RectangleShape rect, Ball *ball) {
		Vector2 pos = Vector2(rect.getPosition().x, rect.getPosition().y);
		Vector2 a(1, 0), b(1, 0), c;
		Vector2 size = Vector2(rect.getSize().x, rect.getSize().y);
		Vector2 prev_pos = (* ball).position;
		float t1, t2, rotation_a;
		int count = 0;
		a.getRotated(rect.getRotation());
		rotation_a = rect.getRotation();
		if ((ball->position.x >= rect.getPosition().x) && (ball->position.x <= rect.getPosition().x + rect.getSize().x) && (ball->position.y >= rect.getPosition().y) && (ball->position.y <= rect.getPosition().y + rect.getSize().y)) {
			return 1;
		}
		return 0;
		
		/*if (collisionOfBallWithline(pos, pos + Vector2(size.x, 0).rotate(rotation_a), *ball)) {
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
			std::cout << (acos((*ball).velocity.norm() * c) * 180 / M_PI) << "\n";
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
		Vector2 a = (pos_end-pos_begin).norm();
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
		}*/
	}
};

#endif	/* COLLISION_H */
