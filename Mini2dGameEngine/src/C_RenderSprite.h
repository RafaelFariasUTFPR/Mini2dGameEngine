#pragma once

#include <SFML/Graphics.hpp>


#include "ComponentMaster.h"

class C_RenderSprite :
    public ComponentMaster
{
public:
    C_RenderSprite(Global* globalVariables, sf::Vector2u _tileCoordinate, sf::Vector2f _dimension, sf::Vector2u _spriteDimensionInPixels);

    void process() override;
    void draw() override;
    void setSpriteParameters(sf::Vector2u _dimensionInPixels);

    void setPivotOffset(sf::Vector2f offset);

    //uint16_t textureNumber;
    sf::Vector2u tileCoordinate;

    // Tamanho que o objeto aparecera na tela
    sf::Vector2f dimension;
    sf::Vector2f pivotOffset = sf::Vector2f(0,0);

    // Dimenção da textura para poder linkar
    sf::Vector2u spriteDimension = sf::Vector2u(2,2);

private:
    sf::VertexArray vertexArr;
    sf::VertexArray quad;


    void updateVertexPosition();

};

