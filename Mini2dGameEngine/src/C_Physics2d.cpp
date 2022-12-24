#include "C_Physics2d.h"

C_Physics2d::C_Physics2d(Global* globalVariables, myMath::Transform initialTransform, std::shared_ptr<C_Collider2d> _collider, bool& _isDynamic) : ComponentMaster(globalVariables)
{
	collider = _collider;
	controlsTransform = true;
	isDynamic = &_isDynamic;


}

C_Physics2d::C_Physics2d(
	Global* globalVariables,
	myMath::Transform initialTransform,
	sf::Vector2f initialSpeed,
	double initialRotationSpeed,
	std::shared_ptr<C_Collider2d> _collider,
	bool& _isDynamic) :
		ComponentMaster(globalVariables)
{
	
	transform = initialTransform;
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

void C_Physics2d::processDeltaTime(double deltaTime)
{
	setRotation(transform.rotation + (getRotationSpeed() * global->deltaTime));
	applyGravity();
	updatePosition(deltaTime);
	ComponentMaster::processDeltaTime(deltaTime);
}

myMath::Transform C_Physics2d::getTransform()
{
	return transform;
}
	
void C_Physics2d::setRotation(double newRotation)
{
	transform.rotation = newRotation; 
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
	lastTransform.position = transform.position;
	calculateSpeed(deltaTime);
	sf::Vector2f newPos = transform.position + (speed) + (0.5f * (acceleration * deltaTime * deltaTime));

	setPosition(newPos);

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

void C_Physics2d::calculateSpeed(float dt)
{
	setSpeed(speed + (acceleration * dt));
}