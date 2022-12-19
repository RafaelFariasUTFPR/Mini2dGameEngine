#include "C_RenderSprite.h"

C_RenderSprite::C_RenderSprite(Global* globalVariables, uint16_t _textureNumber, sf::Vector2u _tileCoordinate, sf::Vector2f _dimension) : ComponentMaster(globalVariables)
{
    textureNumber = _textureNumber;
    tileCoordinate = _tileCoordinate;
    quad = sf::VertexArray(sf::Quads, 4);

    quad[0].position = sf::Vector2f(-_dimension.x / 2, -_dimension.y / 2);
    quad[1].position = sf::Vector2f(_dimension.x / 2, -_dimension.y / 2);
    quad[2].position = sf::Vector2f(_dimension.x / 2, _dimension.y / 2);
    quad[3].position = sf::Vector2f(-_dimension.x / 2, _dimension.y / 2);

    setSpriteParameters(_dimension.x, _dimension.y);

    updateVertexPosition();
}
void C_RenderSprite::setSpriteParameters(float width, float height)
{
    spriteWidth = width;
    spriteHeight = height;


    // Adicionando o offset do tamanho dos tiles na textura
    quad[0].texCoords = sf::Vector2f(global->tileSize * tileCoordinate.x, global->tileSize * tileCoordinate.y);
    quad[1].texCoords = sf::Vector2f(quad[0].texCoords.x + global->tileSize, quad[0].texCoords.y);
    quad[2].texCoords = sf::Vector2f(quad[0].texCoords.x + global->tileSize, quad[0].texCoords.y + global->tileSize);
    quad[3].texCoords = sf::Vector2f(quad[0].texCoords.x, quad[0].texCoords.y + global->tileSize);


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
        quad[i].position = myMath::rotatePointArrounPoint(quad[i].position, sf::Vector2f(0,0), transform.rotation - spriteRotation);
        
        vertexArr[i].position = quad[i].position + transform.position;
    }
    spriteRotation = transform.rotation;
    
}

void C_RenderSprite::process()
{
    ComponentMaster::process();
}