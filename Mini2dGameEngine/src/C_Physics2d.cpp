#include "C_Physics2d.h"

C_Physics2d::C_Physics2d(Global* globalVariables, myMath::Transform initialTransform) : ComponentMaster(globalVariables)
{

	controlsTransform = true;

}

C_Physics2d::C_Physics2d(
	Global* globalVariables,
	myMath::Transform initialTransform,
	sf::Vector2f initialSpeed,
	double initialRotationSpeed) : 
		ComponentMaster(globalVariables)
{
	
	transform = initialTransform;
	setSpeed(initialSpeed);
	setRotationSpeed(initialRotationSpeed);
	controlsTransform = true;

}


void C_Physics2d::process()
{

	setRotation(transform.rotation + (getRotationSpeed() * global->deltaTime));
	setPosition(transform.position + sf::Vector2f((getSpeed().x * global->deltaTime), (getSpeed().y * global->deltaTime)));
	ComponentMaster::process();
}

myMath::Transform C_Physics2d::getTransform()
{
	return transform;
}