#pragma once
#include "ComponentMaster.h"

class C_Collider2d;

struct Collision {
    uint32_t myId = 0;
    uint32_t otherId = 0;
    sf::Vector2f collisionNormal = sf::Vector2f(0, 0);

    //std::shared_ptr<C_Collider2d> otherCollider = nullptr;
    sf::Vector2f displacement = sf::Vector2f(0, 0);
    std::vector<sf::Vector2f> collisionPoints;

};

class C_Collider2d :
    public ComponentMaster
{
public:
    C_Collider2d(sf::VertexArray _collisionVertexArray);
    C_Collider2d();

    void process() override;
    void fixedProcess(double deltaTime) override;
    void draw() override;

    void updatePosition();

    void setCollisionPoligon(sf::VertexArray _collisionVertexArray);
    sf::VertexArray getCollisionPoligon() { return collisionPoligon; }

    void addCollisions(Collision _collision) { collisionsVector.push_back(_collision); }
    void clearCollisions() { collisionsVector.clear(); }
    std::vector<Collision> getCollisionsVector() { return collisionsVector; }
    unsigned int getNumberOfCollisions() { return collisionsVector.size(); }
    void setCollisionsVector(std::vector<Collision> _collisions) { collisionsVector = _collisions; }
    bool isColliding()
    {
        if (collisionsVector.size())
            return true;
        return false;
    }

    bool drawDebug = false;


    double influenceRadius = 0;
private:
    // Shape of the collider
    sf::VertexArray collisionVertexArray;

    // Actual collider
    sf::VertexArray collisionPoligon;

    sf::VertexArray collisionDebugVertexArray;

    std::vector<Collision> collisionsVector;

};

