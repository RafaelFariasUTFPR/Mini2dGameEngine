#pragma once
#include "ComponentMaster.h"



class C_Collider2d :
    public ComponentMaster
{
public:
    C_Collider2d(Global* globalVariables, sf::VertexArray _collisionVertexArray);
    C_Collider2d(Global* globalVariables);

    void process() override;

    void draw() override;

    void setCollisionPoligon(sf::VertexArray _collisionVertexArray);
    sf::VertexArray getCollisionPoligon() { return collisionPoligon; }


    bool drawDebug = false;


    double influenceRadius = 0;

private:
    // Shape of the collider
    sf::VertexArray collisionVertexArray;

    // Actual collider
    sf::VertexArray collisionPoligon;

};

