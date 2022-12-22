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




	void runCollisionSystem(std::vector<std::shared_ptr<C_Physics2d>> physicsCompVec, double dt, Global* global);


}

