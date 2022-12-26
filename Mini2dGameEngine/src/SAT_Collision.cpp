// CREDITOS https://github.com/xSnapi/SAT-Collision

#include "SAT_Collision.h"

namespace SAT
{	
	ColResult SATCollision(C_Collider2d body, C_Collider2d other) {
		float minOverlap = INF;

		ColResult result;

		sf::VertexArray bodyVertices = body.getCollisionPoligon();
		sf::VertexArray otherVertices = other.getCollisionPoligon();

		uint32_t bodyCount = body.getCollisionPoligon().getVertexCount();
		uint32_t otherCount = other.getCollisionPoligon().getVertexCount();

		uint32_t all = bodyCount + otherCount;

		/*
		if (all == 2)
			return SATCollision((const CircleCollider&)body, (const CircleCollider&)other, MTV);
		else if (bodyCount == 1)
			return SATCollision((const CircleCollider&)body, other, MTV);
		else if (otherCount == 1)
			return SATCollision(body, (const CircleCollider&)other, MTV);
		*/

		sf::VertexArray axis(sf::Lines, all);

		for (uint32_t i = 0; i < bodyCount; i++)
			axis[i].position = PerpendicularAxis(bodyVertices, i, bodyCount);

		for (uint32_t i = 0; i < otherCount; i++)
			axis[i + bodyCount].position = PerpendicularAxis(otherVertices, i, otherCount);

		for (uint32_t i = 0; i < all; i++) {
			sf::Vector2f a = axis[i].position;

			sf::Vector2f bodyProjection = ProjectOnto(bodyVertices, bodyCount, a);
			sf::Vector2f otherProjection = ProjectOnto(otherVertices, otherCount, a);

			float overlap = Overlap(bodyProjection, otherProjection);

			if (!overlap) {
				result.displacement = sf::Vector2f(0.0f, 0.0f);
				result.result = false;
				return result;
			}
			else {
				if (overlap < minOverlap) {
					minOverlap = overlap;

					result.displacement = a * overlap;

				}
			}
		}


		// Calculando os pontos de colisão
		std::vector<sf::Vector2f> collidingVertices = getCollidingVertices(body, other);
		result.collisionPoints.insert(result.collisionPoints.end(), collidingVertices.begin(), collidingVertices.end());

		//std::vector<sf::Vector2f> otherCollidingVertices = getCollidingVertices(other, body);
		//result.collisionPoints.insert(result.collisionPoints.end(), otherCollidingVertices.begin(), otherCollidingVertices.end());



		if (myMath::DotProduct(myMath::GetCenter(bodyVertices) - myMath::GetCenter(otherVertices), result.displacement) < 0.0f)
			result.displacement *= -1.0f;
		/*
		if (body.Trigger)
			body.Trigger();

		if (other.Trigger)
			other.Trigger();
		*/

		result.result = true;
		return result;
	}
	/*

	bool Collision::SATCollision(const CircleCollider& body, const Collider& other, sf::Vector2f& MTV) {
		float minOverlap = INF;

		sf::Vector2f center = body.GetPosition();
		float		 radius = body.GetRadius();

		sf::Vector2f* vert = other.m_vertices;

		uint32_t vertCount = other.m_verticesCount;
		uint32_t all = vertCount + 1;

		sf::Vector2f* axis = new sf::Vector2f[all];

		for (uint32_t i = 0; i < vertCount; i++)
			axis[i] = PerpendicularAxis(vert, i, vertCount);

		axis[vertCount] = CircleAxis(vert, vertCount, center);

		for (uint32_t i = 0; i < all; i++) {
			auto& a = axis[i];

			sf::Vector2f circleProjection = ProjectCircle(center, radius, a);
			sf::Vector2f otherProjection = ProjectOnto(vert, vertCount, a);

			float overlap = Overlap(circleProjection, otherProjection);

			if (!overlap) {
				MTV = sf::Vector2f(0.0f, 0.0f);

				delete[] axis;

				return false;
			}
			else {
				if (overlap < minOverlap) {
					minOverlap = overlap;

					MTV = a * overlap;
				}
			}
		}

		if (DotProduct(center - GetCenter(other), MTV) < 0.0f)
			MTV *= -1.0f;

		if (body.Trigger)
			body.Trigger();

		if (other.Trigger)
			other.Trigger();

		delete[] axis;
		return true;
	}

	bool Collision::SATCollision(const Collider& body, const CircleCollider& other, sf::Vector2f& MTV) {
		bool temp = SATCollision(other, body, MTV);
		MTV *= -1.0f;

		return temp;
	}

	bool Collision::SATCollision(const CircleCollider& body, const CircleCollider& other, sf::Vector2f& MTV) {
		sf::Vector2f diff(body.GetPosition() - other.GetPosition());

		float length = Length(diff);
		float sum = body.GetRadius() + other.GetRadius();

		if (length >= sum)
			return false;

		sum -= length;

		diff = Normalize(diff);

		MTV = diff * sum;

		if (body.Trigger)
			body.Trigger();

		if (other.Trigger)
			other.Trigger();

		return true;
	}
	*/
	
	std::vector<sf::Vector2f> getCollidingVertices(C_Collider2d body, C_Collider2d other)
	{
		std::vector<sf::Vector2f> resultVector;
		sf::VertexArray bodyVertices = body.getCollisionPoligon();
		sf::VertexArray otherVertices = other.getCollisionPoligon();

		for (int i = 0; i < bodyVertices.getVertexCount(); i++)
		{
			bool isInside = true;
			for (int j = 1; j < otherVertices.getVertexCount(); j++)
			{
				sf::Vector2f initialLinePoint(otherVertices[j].position);
				sf::Vector2f endLinePoint(otherVertices[j - 1].position);

				if (myMath::doLinesIntersect(bodyVertices[i].position, other.transform->position, initialLinePoint, endLinePoint))
				{
					isInside = false;
					break;
				}

			}

			if(isInside)
				resultVector.push_back(bodyVertices[i].position);

		}
		return resultVector;
	}


	sf::Vector2f CircleAxis(sf::VertexArray vertices, uint32_t count, sf::Vector2f center) {
		sf::Vector2f axis;

		uint32_t index = 0;
		float	 dist = INF;

		for (uint32_t i = 0; i < count; i++) {
			auto& v = vertices[i];

			float d = myMath::Distance(v.position, center);

			if (d >= dist)
				continue;

			dist = d;
			index = i;
		}
		return myMath::Normalize(center - vertices[index].position);
	}

	sf::Vector2f PerpendicularAxis(sf::VertexArray vertices, uint32_t index, uint32_t count){
		uint32_t i0 = index + 1;
		uint32_t i1 = index;

		if (i0 == count) {
			i0 = 0;
			i1 = count - 1;
		}

		sf::Vector2f v = myMath::Normalize(vertices[i0].position - vertices[i1].position);


		return
		{
			-v.y,
			 v.x
		};
	}

	sf::Vector2f ProjectOnto(sf::VertexArray vertices, uint32_t count, sf::Vector2f axis){
		float min = INF;
		float max = -INF;

		for (uint32_t i = 0; i < count; i++) {
			float projection = myMath::DotProduct(vertices[i].position, axis);

			if (projection < min)
				min = projection;

			if (projection > max)
				max = projection;
		}

		return
		{
			min,
			max
		};
	}

	sf::Vector2f ProjectCircle(sf::Vector2f center, float radius, sf::Vector2f axis){
		sf::Vector2f dir = radius * axis;

		sf::Vector2f p1 = center + dir;
		sf::Vector2f p2 = center - dir;

		float min = myMath::DotProduct(p1, axis);
		float max = myMath::DotProduct(p2, axis);

		if (min > max)
			std::swap(min, max);

		return
		{
			min,
			max
		};
	}

	float Overlap(sf::Vector2f v0, sf::Vector2f v1){
		return !(v0.x <= v1.y && v0.y >= v1.x) ? 0.0f : std::min(v0.y, v1.y) - std::max(v0.x, v1.x);
	}

}