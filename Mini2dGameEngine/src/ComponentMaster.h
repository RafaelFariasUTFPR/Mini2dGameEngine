#pragma once

#include "Global.h"
class ComponentMaster
{
public:
	ComponentMaster(Global* globalVariables);
	virtual void beginPlay() {}
	virtual void process() {}
	virtual void endGame() {}
	virtual void draw() {}


protected:
	Global* global;
};

