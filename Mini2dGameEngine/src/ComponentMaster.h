#pragma once


class ComponentMaster
{
public:
	ComponentMaster();
	virtual void beginPlay();
	virtual void process();
	virtual void endGame();
};

