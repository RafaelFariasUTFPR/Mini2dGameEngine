#include "EntityMaster.h"

EntityMaster::EntityMaster(Global* globalVariables, std::string myName, myMath::Transform initialTransform) : componentHandler(globalVariables, &transform, &id, &isDynamic)
{
	global = globalVariables;
	name = myName;
	transform = initialTransform;
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

void EntityMaster::fixedProcess(double deltaTime)
{
	componentHandler.fixedProcess(deltaTime);
}


void EntityMaster::endGame()
{
	componentHandler.endGame();
}

void EntityMaster::draw()
{
	componentHandler.draw();
}