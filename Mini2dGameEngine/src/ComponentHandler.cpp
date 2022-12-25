#include "ComponentHandler.h"


ComponentHandler::ComponentHandler(Global* globalVariables, myMath::Transform* enttTransform, uint32_t* _myId, bool* _isDynamic)
{
	global = globalVariables;
	transform = enttTransform;
	myId = _myId;
	isDynamic = _isDynamic;
}

ComponentHandler::~ComponentHandler()
{

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
		componentVec.at(i)->process();
	}

}

void ComponentHandler::fixedProcess(double deltaTime)
{
	for (int i = 0; i < componentVec.size(); i++)
	{
		componentVec.at(i)->fixedProcess(deltaTime);
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

void ComponentHandler::addComponent(std::shared_ptr<ComponentMaster> component)
{
	componentVec.push_back(component);
	component->setPointers(global, transform, myId, isDynamic);
}
