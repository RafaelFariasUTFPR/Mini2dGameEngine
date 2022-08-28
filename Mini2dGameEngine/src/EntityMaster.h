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
	virtual void beforePlay();
	virtual void beginPlay();
	virtual void process();
	virtual void endGame();
	virtual void draw();


	std::string name;
	int id;

protected:
	Global* global;
	ComponentHandler componentHandler;


};

