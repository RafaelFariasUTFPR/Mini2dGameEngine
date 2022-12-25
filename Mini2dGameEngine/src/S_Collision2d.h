#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <thread>

#include "MyMath.h"
#include "C_Physics2d.h"
#include "C_Collider2d.h"
#include "SAT_Collision.h"

#include "EntityMaster.h"


namespace Coll2d
{
	const sf::Color debugLineColor = sf::Color::Cyan;


	//void threadedCollisionSystem(uint32_t startIndex, uint32_t endIndex, std::vector<std::shared_ptr<C_Collider2d>> colliderCompVec, std::vector<Collision>* resultCollisionVector);

	std::vector<Collision> runCollisionSystem(std::vector<std::shared_ptr<C_Collider2d>> colliderCompVec);

	void solvePhysicsCollisions(std::vector<std::shared_ptr<C_Physics2d>> physicsCompVec, std::vector<Collision>collisionsVector, double dt);



}

