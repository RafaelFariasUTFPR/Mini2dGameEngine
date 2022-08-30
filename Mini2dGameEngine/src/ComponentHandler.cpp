#include "ComponentHandler.h"


ComponentHandler::ComponentHandler(Global* globalVariables)
{
	global = globalVariables;
	transform.position = sf::Vector2f(200, 200);
}

ComponentHandler::~ComponentHandler()
{

	for (int i = 0; i < componentVec.size(); i++)
		delete componentVec.at(i);
}

void ComponentHandler::beforePlay()
{
	for (int i = 0; i < componentVec.size(); i++)
		componentVec.at(i)->beforePlay();
}
void ComponentHandler::beginPlay()
{
	for (int i = 0; i < componentVec.size(); i++)
		componentVec.at(i)->beginPlay();
}

void ComponentHandler::process()
{
	for (int i = 0; i < componentVec.size(); i++)
	{
		if (componentVec.at(i)->controlsTransform)
			transform = componentVec.at(i)->getTransform();
		else
			componentVec.at(i)->setTransform(transform);
	
		componentVec.at(i)->process();
	}

}

void ComponentHandler::draw()
{
	for (int i = 0; i < componentVec.size(); i++)
		componentVec.at(i)->draw();
}

void ComponentHandler::endGame()
{
	for (int i = 0; i < componentVec.size(); i++)
		componentVec.at(i)->endGame();
}

void ComponentHandler::addComponent(ComponentMaster* component)
{
	componentVec.push_back(component);
}
