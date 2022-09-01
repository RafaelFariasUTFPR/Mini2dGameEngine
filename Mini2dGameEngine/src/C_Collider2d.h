#pragma once
#include "ComponentMaster.h"
class C_Collider2d :
    public ComponentMaster
{
public:
    C_Collider2d(Global* globalVariables, sf::VertexArray& _collisionVertexArray);

    void process() override;

    void draw() override;

    sf::VertexArray* collisionVertexArray;
    sf::VertexArray collisionPoligon;

    bool drawDebug = false;

};

