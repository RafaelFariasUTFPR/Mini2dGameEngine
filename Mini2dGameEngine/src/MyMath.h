
#pragma once
#define PI 3.14159265

#include <SFML/Graphics.hpp>
#include <math.h>
#include <atomic>
#include <iostream>


namespace myMath
{

	struct Transform
	{
		sf::Vector2f position = sf::Vector2f(0, 0);
		sf::Vector2f scale = sf::Vector2f(1, 1);
		float rotation = 0;

		bool operator==(const Transform T1)
		{
			if (
				this->position == T1.position &&
				this->scale == T1.scale &&
				this->rotation == T1.rotation)
				return true;
			return false;
		}
	};

	struct CollResult
	{
		sf::Vector2f velocity1;
		sf::Vector2f velocity2;

	};


	sf::Vector2f rotatePointArrounPoint(sf::Vector2f myPoint, sf::Vector2f centerPoint, float rotationAngle);

	// Metodo diferente para testar interseção
	sf::Vector2f calcDisplacement(sf::Vector2f p1, sf::Vector2f q1, sf::Vector2f p2, sf::Vector2f q2);

	bool doLinesIntersect(sf::Vector2f p1, sf::Vector2f q1, sf::Vector2f p2, sf::Vector2f q2);


	double deg2rad(double angle);

	double distBetweenPoints(sf::Vector2f p1, sf::Vector2f p2);



	float DotProduct(sf::Vector2f v0, sf::Vector2f v1);

	float CrossProduct(sf::Vector2f v0, sf::Vector2f v1);

	float Distance(sf::Vector2f v0, sf::Vector2f v1);

	float Length(sf::Vector2f v);

	sf::Vector2f Normalize(sf::Vector2f v);

	sf::Vector2f GetCenter(sf::VertexArray body);


	//sf::Vector2f VecAbs(sf::Vector2f v);

	sf::Vector2f GetReflection(sf::Vector2f v, sf::Vector2f normal);


	CollResult calculateInelasticCollision(sf::Vector2f velocity1, float mass1, sf::Vector2f velocity2, float mass2, float elasticity);
}


