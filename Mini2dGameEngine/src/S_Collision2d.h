#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <thread>
#include <future>
#include <queue>


#include <CTPL/ctpl_stl.h>


#include "MyMath.h"
#include "C_Physics2d.h"
#include "C_Collider2d.h"
#include "SAT_Collision.h"

#include "EntityMaster.h"


namespace Coll2d
{


	const sf::Color debugLineColor = sf::Color::Cyan;

	// Todas as funções que irão para a thread pool precisam do "id" como primeiro argumento
	std::vector<Collision> threadedCollisionSystem(int id, uint32_t startIndex, uint8_t n_ofThreadsUsed, std::vector<std::shared_ptr<C_Collider2d>> colliderCompVec);

	std::vector<Collision> runCollisionSystem(std::vector<std::shared_ptr<C_Collider2d>> colliderCompVec, ctpl::thread_pool* threadPool, std::mutex* operateEnttMutex);

	void solvePhysicsCollisions(std::vector<std::shared_ptr<C_Physics2d>> physicsCompVec, std::vector<Collision>collisionsVector, double dt);



}

