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
	setRotation(transform.rotation + (getRotationSpeed() * global->deltaTime));
	applyGravity();
	updatePosition();


	ComponentMaster::process();
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
void C_Physics2d::updatePosition()
{
	if (!*isDynamic)
		return;

	const sf::Vector2f displacement = transform.position - lastTransform.position;
	lastTransform.position = transform.position;

	float dt = global->deltaTime;

	sf::Vector2f newPos = (transform.position + displacement + (acceleration * dt * dt)) ;
	
	setPosition(newPos);


	acceleration = {};

}

void C_Physics2d::applyGravity()
{
	if (*isDynamic)
	{
		accelerate(gravity);
	}
}

