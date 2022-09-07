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
	EntityMaster(Global* globalVariables, std::string myName);
	~EntityMaster();
	virtual void beforePlay();
	virtual void beginPlay();
	virtual void process();
	virtual void endGame();
	virtual void draw();


	std::string name;
	int id;

	//Standard Variables
	myMath::Transform transform;

	// A entidade possui capacidade de se mover?
	bool isDynamic = false;

	ComponentHandler componentHandler;
protected:
	Global* global;




};

