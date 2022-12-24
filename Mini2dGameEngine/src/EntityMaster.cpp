#include "EntityMaster.h"

EntityMaster::EntityMaster(Global* globalVariables, std::string myName) : componentHandler(globalVariables, &transform)
{

	global = globalVariables;
	name = myName;
}

EntityMaster::~EntityMaster()
{

}

void EntityMaster::beforePlay()
{
	componentHandler.beforePlay();
}


void EntityMaster::beginPlay()
{
	componentHandler.beginPlay();
}

void EntityMaster::process()
{
	componentHandler.process();
}

void EntityMaster::endGame()
{
	componentHandler.endGame();
}

void EntityMaster::draw()
{
	componentHandler.draw();
}