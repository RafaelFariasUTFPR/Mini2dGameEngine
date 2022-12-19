#pragma once

#include <SFML/Graphics.hpp>


#include "ComponentMaster.h"

class C_RenderSprite :
    public ComponentMaster
{
public:
    C_RenderSprite(Global* globalVariables, uint16_t _textureNumber, sf::Vector2u _tileCoordinate, sf::Vector2f _dimension);

    void process() override;
    void draw() override;
    void setSpriteParameters(float width, float height);


    uint16_t textureNumber;
    sf::Vector2u tileCoordinate;
    float spriteWidth = 2;
    float spriteHeight = 2;

private:
    sf::VertexArray vertexArr;
    sf::VertexArray quad;

    float spriteRotation = 0;

    void updateVertexPosition();

};

