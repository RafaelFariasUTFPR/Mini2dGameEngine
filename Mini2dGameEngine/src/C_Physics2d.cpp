#include "C_Physics2d.h"

C_Physics2d::C_Physics2d(
	std::shared_ptr<C_Collider2d> _collider, 
	bool& _isDynamic) : ComponentMaster()
{
	collider = _collider;
	controlsTransform = true;
	isDynamic = &_isDynamic;


}

C_Physics2d::C_Physics2d(
	sf::Vector2f initialSpeed,
	double initialRotationSpeed,
	std::shared_ptr<C_Collider2d> _collider,
	bool& _isDynamic) : ComponentMaster()
{
	
	setSpeed(initialSpeed);
	setRotationSpeed(initialRotationSpeed);
	collider = _collider;
	controlsTransform = true;
	isDynamic = &_isDynamic;

}


void C_Physics2d::process()
{

	ComponentMaster::process();
}

void C_Physics2d::fixedProcess(double deltaTime)
{
	setRotation(transform->rotation + (getRotationSpeed() * deltaTime));
	applyGravity();
	updatePosition(deltaTime);
	ComponentMaster::fixedProcess(deltaTime);
}

	
void C_Physics2d::setRotation(double newRotation)
{
	transform->rotation = newRotation; 
}
void C_Physics2d::accelerate(sf::Vector2f _acceleration)
{
	acceleration += _acceleration;
	//std::cout << acceleration.y << std::endl;
}
void C_Physics2d::updatePosition(float deltaTime)
{
	if (!*isDynamic)
		return;

	applyGravity();
	//setSpeed((transform.position - lastTransform.position));
	lastTransform.position = transform->position;
	calculateSpeed(deltaTime);
	sf::Vector2f newPos = transform->position + (speed) + (0.5f * (acceleration * deltaTime * deltaTime));

	setPosition(newPos);
	setRotation(transform->rotation + (rotationSpeed * deltaTime));

	//std::cout << acceleration.y << std::endl;
	acceleration = {};

}

void C_Physics2d::applyGravity()
{
	if (*isDynamic)
	{
		accelerate(gravity);
	}
}

void C_Physics2d::applyTorque(float radius, float force, float angle)
{
	float torque = radius * force * sin(angle);
	float angularAcceleration = torque / momentOfInertia;
	accelerateAngularRotation(angularAcceleration);
}

void C_Physics2d::accelerateAngularRotation(float acceleration)
{
	setRotationSpeed(getRotationSpeed() + (acceleration * global->deltaTime));
}



void C_Physics2d::calculateSpeed(float dt)
{
	setSpeed(speed + (acceleration * dt));
}