#include "ComponentHandler.h"


ComponentHandler::ComponentHandler(Global* globalVariables)
{
	global = globalVariables;
}

ComponentHandler::~ComponentHandler()
{
	for (int i = 0; i < entityVec.size(); i++)
		delete entityVec.at(i);
}


void ComponentHandler::draw()
{
	for (int i = 0; i < entityVec.size(); i++)
		entityVec.at(i)->draw();
}

void ComponentHandler::addComponent(ComponentMaster* component)
{
	entityVec.push_back(component);
}