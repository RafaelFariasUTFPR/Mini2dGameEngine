#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "MyMath.h"
#include "C_Physics2d.h"
#include "C_Collider2d.h"
#include "SAT_Collision.h"

#include "EntityMaster.h"


namespace Coll2d
{
	const sf::Color debugLineColor = sf::Color::Cyan;




	std::vector<Collision> runCollisionSystem(std::vector<std::shared_ptr<C_Collider2d>> colliderCompVec);

	void solvePhysicsCollisions(std::vector<std::shared_ptr<EntityMaster>> entityVec, std::vector<Collision>collisionsVector, double dt);



}

