#pragma once
#include "../EntityMaster.h"
#include "../Global.h"

#include "../C_RenderSprite.h"
#include "../C_Physics2d.h"
#include "../C_Collider2d.h"
class Cube :
    public EntityMaster
{
public:
    Cube(Global* globalVariables, std::string myName) : EntityMaster(globalVariables, myName)
    {
        componentHandler.addComponent(renderComponent);
        componentHandler.addComponent(physicsComponent);
        componentHandler.addComponent(colliderComponent);


        // Boundaries of the collision polygon
        sf::VertexArray collisionVertexArray;
        collisionVertexArray.append(sf::Vertex(sf::Vector2f(-25, -25)));
        collisionVertexArray.append(sf::Vertex(sf::Vector2f(25, -25)));
        collisionVertexArray.append(sf::Vertex(sf::Vector2f(25, 25)));
        collisionVertexArray.append(sf::Vertex(sf::Vector2f(-25, 25)));
        //collisionVertexArray.append(sf::Vertex(sf::Vector2f(-25, -25)));
        colliderComponent->drawDebug = true;
        colliderComponent->setCollisionPoligon(collisionVertexArray);

        isDynamic = true;
        // Adicionando os componentes




    }

    //Quando fizer override da função parent deve chamar a função no Base
    void beginPlay() override;
    void process() override;


    // Criando os componenetes
    std::shared_ptr<C_RenderSprite> renderComponent = std::make_shared<C_RenderSprite>(sf::Vector2u(0,0), sf::Vector2f(50,50), sf::Vector2u(256,256));
    std::shared_ptr<C_Collider2d> colliderComponent = std::make_shared<C_Collider2d>();
    std::shared_ptr<C_Physics2d> physicsComponent = std::make_shared<C_Physics2d>(colliderComponent, isDynamic);

};

