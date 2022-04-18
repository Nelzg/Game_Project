#pragma once
#include "../../../src/Vector2.h"

class MaterialPoint
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
		position.x = position.x + dt * velocity.x;
		position.y = position.y + dt * velocity.y;
	}

	virtual void UpdateVelocity(float dt) {
		velocity.x = velocity.x + dt * acceleration.x;
		velocity.y = velocity.y + dt * acceleration.y;
	}

	Vector2 GetImpulse() const {
		return { 0, 0 };
	}
};

