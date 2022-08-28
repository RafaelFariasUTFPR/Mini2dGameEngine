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
	~EntityMaster();
	virtual void beginPlay();
	virtual void process();
	virtual void endGame();


	std::string name;
	int id;
	std::vector<ComponentMaster*> myComponents;

protected:
	Global* global;
	ComponentHandler componentHandler;


};

