#pragma once

#include <string>
#include <iostream>

#include "Global.h"
#include "ComponentHandler.h"


//Entity Base Class
class EntityMaster
{
public:
	EntityMaster(Global* globalVariables, std::string myName);
	
	virtual void beginPlay();
	virtual void process();
	virtual void endGame();


	std::string name;
	int id;

protected:
	Global* global;
	ComponentHandler componentHandler;


};

