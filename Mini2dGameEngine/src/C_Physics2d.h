#pragma once

#include "ComponentMaster.h"
#include "MyMath.h"

#include "C_Collider2d.h"

class C_Physics2d :
    public ComponentMaster
{
public:
    C_Physics2d(Global* globalVariables, myMath::Transform initialTransform, std::shared_ptr<C_Collider2d> _collider, bool& _isDynamic);
    C_Physics2d(
        Global* globalVariables, 
        myMath::Transform initialTransform,
        sf::Vector2f initialSpeed,
        double initialRotationSpeed,
        std::shared_ptr<C_Collider2d> _collider,
        bool& _isDynamic);

    void process() override;

    myMath::Transform getTransform() override;


    sf::Vector2f getSpeed() { return speed; }
    double getRotationSpeed() { return rotationSpeed; }
    bool getIsDynamic() { return *isDynamic; }

    void setPosition(sf::Vector2f newPosition) { transform.position = newPosition; }
    void setRotation(double newRotation);
    void setSpeed(sf::Vector2f newSpeed) { speed = newSpeed; }
    void setRotationSpeed(double newRotationSpeed) { rotationSpeed = newRotationSpeed; }


    float gravity = 0;

    // Define se o sistema de colisão pode mover ou não a entidade
    bool isSolid = true;



    myMath::Transform transform;

    std::shared_ptr<C_Collider2d> collider;

private:
    sf::Vector2f speed;
    double rotationSpeed = 0;

    // Ponteiro para a variavel "isDynamic" da entidade
    bool* isDynamic;
};

