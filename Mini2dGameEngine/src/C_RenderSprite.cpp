#include "C_RenderSprite.h"

C_RenderSprite::C_RenderSprite(Global* globalVariables, sf::Vector2u _tileCoordinate, sf::Vector2f _dimension, sf::Vector2u _spriteDimensionInPixels) : ComponentMaster(globalVariables)
{
    tileCoordinate = _tileCoordinate;
    quad = sf::VertexArray(sf::Quads, 4);
    quad[0].position = sf::Vector2f(-_dimension.x / 2.0f, -_dimension.y / 2.0f) + pivotOffset;
    quad[1].position = sf::Vector2f(_dimension.x / 2.0f, -_dimension.y / 2.0f) + pivotOffset;
    quad[2].position = sf::Vector2f(_dimension.x / 2.0f, _dimension.y / 2.0f) + pivotOffset;
    quad[3].position = sf::Vector2f(-_dimension.x / 2.0f, _dimension.y / 2.0f) + pivotOffset;

    setSpriteParameters(_spriteDimensionInPixels);

    updateVertexPosition();
}

void C_RenderSprite::setPivotOffset(sf::Vector2f offset)
{
    for (int i = 0; i < quad.getVertexCount(); i++)
        quad[i].position += pivotOffset;
}


void C_RenderSprite::setSpriteParameters(sf::Vector2u _dimensionInPixels)
{
    spriteDimension = _dimensionInPixels;


    // Adicionando o offset do tamanho dos tiles na textura
    quad[0].texCoords = sf::Vector2f(tileCoordinate.x, tileCoordinate.y);
    quad[1].texCoords = sf::Vector2f(quad[0].texCoords.x + spriteDimension.x, quad[0].texCoords.y);
    quad[2].texCoords = sf::Vector2f(quad[0].texCoords.x + spriteDimension.x, quad[0].texCoords.y + spriteDimension.y);
    quad[3].texCoords = sf::Vector2f(quad[0].texCoords.x, quad[0].texCoords.y + spriteDimension.y);


    vertexArr = quad;
}


void C_RenderSprite::draw()
{
    updateVertexPosition();

    for (int i = 0; i < vertexArr.getVertexCount(); i++)
        global->sceneBuffer.vArray.append(vertexArr[i]);

    ComponentMaster::draw();
}

void C_RenderSprite::updateVertexPosition()
{

    for (int i = 0; i < quad.getVertexCount(); i++)
    {
        vertexArr[i].position = quad[i].position + transform.position;
        vertexArr[i].position = myMath::rotatePointArrounPoint(vertexArr[i].position, transform.position, transform.rotation);
    }
    
    
}




void C_RenderSprite::process()
{
    ComponentMaster::process();
}