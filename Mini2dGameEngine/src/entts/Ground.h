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
    Ground(Global* globalVariables, std::string myName, myMath::Transform initialTransform) : EntityMaster(globalVariables, myName, initialTransform)
    {
        componentHandler.addComponent(renderComponent);
        componentHandler.addComponent(physicsComponent);
        componentHandler.addComponent(colliderComponent);

        // Boundaries of the collision polygon
        sf::VertexArray collisionVertexArray;
        collisionVertexArray.append(sf::Vertex(sf::Vector2f(-128, -20)));
        collisionVertexArray.append(sf::Vertex(sf::Vector2f(128, -20)));
        collisionVertexArray.append(sf::Vertex(sf::Vector2f(128, 20)));
        collisionVertexArray.append(sf::Vertex(sf::Vector2f(-128, 20)));
        //collisionVertexArray.append(sf::Vertex(sf::Vector2f(-128, -20)));
        //colliderComponent->drawDebug = true;
        colliderComponent->setCollisionPoligon(collisionVertexArray);

        // Setando massa como infinita
        physicsComponent->mass = 0;
        isDynamic = false;
        // Adicionando os componentes


        


    }

    //Quando fizer override da fun��o parent deve chamar a fun��o no Base
    void beforePlay() override
    {
        EntityMaster::beforePlay();
    }




    // Criando os componenetes
    std::shared_ptr<C_RenderSprite> renderComponent = std::make_shared<C_RenderSprite>(sf::Vector2u(256, 0), sf::Vector2f(256, 40), sf::Vector2u(256, 40));
    std::shared_ptr<C_Collider2d> colliderComponent = std::make_shared<C_Collider2d>();
    std::shared_ptr<C_Physics2d> physicsComponent = std::make_shared<C_Physics2d>(colliderComponent, isDynamic);

};

