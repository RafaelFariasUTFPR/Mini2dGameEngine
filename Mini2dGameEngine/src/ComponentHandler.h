#pragma once

#include <vector>
#include <iostream>

#include "ComponentMaster.h"
#include "Global.h"

class ComponentHandler
{
public:
	ComponentHandler(Global* globalVariables);
	~ComponentHandler();

	void beforePlay();
	void beginPlay();
	void process();
	void draw();
	void endGame();

	void addComponent(ComponentMaster* component);


	//Standard Variables
	myMath::Transform transform;


	std::vector<ComponentMaster*>componentVec;
private:
	Global* global;

};

