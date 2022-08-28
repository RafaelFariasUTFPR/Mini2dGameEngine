#include "EntityMaster.h"

EntityMaster::EntityMaster(Global* globalVariables, std::string myName) : componentHandler(globalVariables)
{
	global = globalVariables;
	name = myName;
}

EntityMaster::~EntityMaster()
{
	std::cout << "DELETED\n";
	for (int i = 0; i < myComponents.size(); i++)
		delete myComponents.at(i);
}

void EntityMaster::beginPlay()
{

}

void EntityMaster::process()
{

}

void EntityMaster::endGame()
{

}