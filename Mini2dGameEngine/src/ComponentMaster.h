#pragma once


#include <iostream>


#include "Global.h"
#include "MyMath.h"

class ComponentMaster
{
public:
	ComponentMaster();

	virtual void beforePlay() {}
	virtual void beginPlay() {}
	virtual void process() {}
	virtual void fixedProcess(double deltaTime) {}
	virtual void endGame() {}
	virtual void draw() {}

	void setPointers(Global* globalVariables, myMath::Transform* enttTransform, uint32_t* _myId, bool* _isDynamic);

	virtual myMath::Transform getTransform() { return *transform; }
	void setTransform(myMath::Transform _transform) { *transform = _transform; }

	uint32_t getMyId() { return *myId; }
	bool getIsDynamic() { return *isDynamic; }

	bool controlsTransform = false;
	myMath::Transform* transform;

	uint32_t* myId;
	// Ponteiro para a variavel "isDynamic" da entidade
protected:
	Global* global;
	bool* isDynamic;

};

