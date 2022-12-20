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
	float deltaGain = global->deltaTime * 2200;
	setRotation(transform.rotation + (getRotationSpeed() * global->deltaTime));
	setPosition(transform.position + sf::Vector2f((getSpeed().x * global->deltaTime), (getSpeed().y * global->deltaTime)));
	velocity.x = (transform.position.x - lastPosition.x) * deltaGain;
	velocity.y = (transform.position.y - lastPosition.y) * deltaGain;
	lastPosition = transform.position;
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