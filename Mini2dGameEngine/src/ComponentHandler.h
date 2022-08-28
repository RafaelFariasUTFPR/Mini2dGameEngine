#pragma once

#include <vector>
#include <iostream>

#include "ComponentMaster.h"
#include "Global.h"

class ComponentHandler
{
public:
	ComponentHandler(Global* globalVariables);

	void beginPlay();
	void process();
	void draw();
	void endGame();

private:
	Global* global;
	std::vector<ComponentMaster*>entityVec;

};

