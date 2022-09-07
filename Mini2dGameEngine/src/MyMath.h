
#pragma once
#define PI 3.14159265

#include <SFML/Graphics.hpp>
#include <math.h>
namespace myMath
{

	struct Transform
	{
		sf::Vector2f position = sf::Vector2f(0, 0);
		sf::Vector2f scale = sf::Vector2f(1, 1);
		double rotation = 0;
	};


	sf::Vector2f rotatePointArrounPoint(sf::Vector2f myPoint, sf::Vector2f centerPoint, float rotationAngle);

	bool doLinesIntersect(sf::Vector2f p1, sf::Vector2f q1, sf::Vector2f p2, sf::Vector2f q2);

	double deg2rad(double angle);

	double distBetweenPoints(sf::Vector2f p1, sf::Vector2f p2);

}


