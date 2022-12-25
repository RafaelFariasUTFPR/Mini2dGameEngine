#pragma once

#include <string>
#include <iostream>
#include <memory>

#include "Global.h"
#include "ComponentHandler.h"


//Entity Base Class
class EntityMaster
{
public:
	EntityMaster(Global* globalVariables, std::string myName, myMath::Transform initialTransform);

	~EntityMaster();
	virtual void beforePlay();
	virtual void beginPlay();
	virtual void process();
	virtual void fixedProcess(double deltaTime);
	virtual void endGame();
	virtual void draw();


	std::string name;
	uint32_t id;

	//Standard Variables
	myMath::Transform transform;

	// A entidade possui capacidade de se mover?
	bool isDynamic = false;

	ComponentHandler componentHandler;
protected:
	Global* global;




};

