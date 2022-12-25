#pragma once

#include <vector>
#include <iostream>
#include <mutex>
#include <queue>

#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds


#include "EntityMaster.h"
#include "entts/Cube.h"
#include "C_Collider2d.h"

#include "S_Collision2d.h"


class EnttHandler
{
public:
	EnttHandler(Global& globalVariables);


	void beforePlay();
	void beginPlay();
	void physicsProcess();

	void process();
	void draw();
	void endGame();


	void addEntt(std::shared_ptr<EntityMaster> entity);


	void deleteEntt(int enttId);

	std::shared_ptr<EntityMaster> getEntityAt(int index)
	{
		return entityVec.at(index);

	}

	int getEntityVecSize() { return entityVec.size(); }


private:
	Global* global;
	
	std::vector<std::shared_ptr<EntityMaster>> entityVec;
	std::vector<std::shared_ptr<C_Collider2d>> colliderCompVec;
	std::vector<Collision> collisionsVector;
	
	sf::Clock physicsClock;
	uint8_t physicsHertz = 60;
	float stepDt = 1.0f / (float)physicsHertz;
	float substepDt;

	//std::queue<uint32_t> availableIndexes;
	std::mutex operateEnttMutex;
};

