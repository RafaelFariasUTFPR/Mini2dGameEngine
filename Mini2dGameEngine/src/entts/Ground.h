#pragma once

#include <iostream>

#include "../EntityMaster.h"
#include "../Global.h"

#include "../C_RenderSprite.h"
#include "../C_Physics2d.h"
#include "../C_Collider2d.h"
class Ground :
    public EntityMaster
{
public:
    Ground(Global* globalVariables, std::string myName) : EntityMaster(globalVariables, myName)
    {
        // Boundaries of the collision polygon
        sf::VertexArray collisionVertexArray;
        collisionVertexArray.append(sf::Vertex(sf::Vector2f(-150, -20)));
        collisionVertexArray.append(sf::Vertex(sf::Vector2f(150, -20)));
        collisionVertexArray.append(sf::Vertex(sf::Vector2f(150, 20)));
        collisionVertexArray.append(sf::Vertex(sf::Vector2f(-150, 20)));
        collisionVertexArray.append(sf::Vertex(sf::Vector2f(-150, -20)));
        colliderComponent->drawDebug = true;
        colliderComponent->setCollisionPoligon(collisionVertexArray);

        isDynamic = false;
        // Adicionando os componentes
        //componentHandler.addComponent(renderComponent);
        componentHandler.addComponent(physicsComponent);
        componentHandler.addComponent(colliderComponent);



    }

    //Quando fizer override da função parent deve chamar a função no Base
    void beforePlay() override
    {
        physicsComponent->setPosition(sf::Vector2f(200, 300));
        physicsComponent->setRotation(10);
        EntityMaster::beforePlay();
    }




    // Criando os componenetes
    std::shared_ptr<C_RenderSprite> renderComponent = std::make_shared<C_RenderSprite>(global, "./resources/ground.png", sf::Vector2f(1, 1));
    std::shared_ptr<C_Collider2d> colliderComponent = std::make_shared<C_Collider2d>(global);
    std::shared_ptr<C_Physics2d> physicsComponent = std::make_shared<C_Physics2d>(global, transform, colliderComponent, isDynamic);

};

