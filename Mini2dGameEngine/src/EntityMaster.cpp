#include "EntityMaster.h"

EntityMaster::EntityMaster(Global* globalVariables, std::string myName) : componentHandler(globalVariables)
{
	global = globalVariables;
	name = myName;
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