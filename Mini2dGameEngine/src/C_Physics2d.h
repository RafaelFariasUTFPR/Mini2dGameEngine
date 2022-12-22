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
    void processDeltaTime(double deltaTime) override;

    sf::Vector2f getSpeed() { return speed; }
    double getRotationSpeed() { return rotationSpeed; }
    bool getIsDynamic() { return *isDynamic; }
    myMath::Transform getTransform();

    void setPosition(sf::Vector2f newPosition) { transform.position = newPosition; }
    void setRotation(double newRotation);
    void setSpeed(sf::Vector2f newSpeed) { speed = newSpeed; }


    void setRotationSpeed(double newRotationSpeed) { rotationSpeed = newRotationSpeed; }

    void accelerate(sf::Vector2f _acceleration);


    // Define se o sistema de colisão pode mover ou não a entidade
    bool isSolid = true;
    float mass = 1.0;

    sf::Vector2f gravity = sf::Vector2f(0, 100);

    myMath::Transform transform;
    myMath::Transform lastTransform;

    std::shared_ptr<C_Collider2d> collider;

private:
    void updatePosition(double deltaTime);
    void applyGravity();
    sf::Vector2f speed;
    
    sf::Vector2f acceleration = sf::Vector2f(0,0);
    double rotationSpeed = 0;

    // Ponteiro para a variavel "isDynamic" da entidade
    bool* isDynamic;
};

