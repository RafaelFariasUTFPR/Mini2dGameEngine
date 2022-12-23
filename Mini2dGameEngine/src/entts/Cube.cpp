#include "Cube.h"

/*/Inicializando a classe derivada junto com a classe base
Cube::Cube(Global* globalVariables, std::string myName) : EntityMaster(globalVariables, myName)
{

	myComponents
}
*/

void Cube::beginPlay()
{
	// Chamando o metodo na classe base	
	EntityMaster::beginPlay();


}

void Cube::process()
{
	float movementSpeed = 20 * global->deltaTime;
	sf::Vector2f movementVector = sf::Vector2f();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		movementVector += sf::Vector2f(-movementSpeed, 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		movementVector += sf::Vector2f(movementSpeed, 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		movementVector += sf::Vector2f(0, -movementSpeed);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		movementVector += sf::Vector2f(0, movementSpeed);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		physicsComponent->setRotation(physicsComponent->transform.rotation - (60 * global->deltaTime));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
	{
		physicsComponent->setRotation(physicsComponent->transform.rotation + (60 * global->deltaTime));
	}



	physicsComponent->setPosition(movementVector + physicsComponent->getTransform().position);

	EntityMaster::process();
}