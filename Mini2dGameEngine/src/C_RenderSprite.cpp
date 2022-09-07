#include "C_RenderSprite.h"

C_RenderSprite::C_RenderSprite(Global* globalVariables, std::string texturePath, sf::Vector2f _initialScale) : ComponentMaster(globalVariables)
{

    texture.loadFromFile(texturePath);
    sprite.setTexture(texture);
    initialScale = _initialScale;

    centerOffset = sf::Vector2f(texture.getSize().x / 2, texture.getSize().y / 2);
    sprite.setPosition(transform.position - centerOffset);

}

void C_RenderSprite::draw()
{
    global->window.draw(sprite);
    ComponentMaster::draw();
}

void C_RenderSprite::process()
{
    sprite.setScale(sf::Vector2f(initialScale.x * transform.scale.x, initialScale.y * transform.scale.y));
    sprite.setPosition(transform.position - centerOffset);
    sprite.setRotation(transform.rotation);
    ComponentMaster::process();
}