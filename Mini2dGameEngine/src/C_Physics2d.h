#pragma once

#include "ComponentMaster.h"
#include "MyMath.h"

class C_Physics2d :
    public ComponentMaster
{
public:
    C_Physics2d(Global* globalVariables, myMath::Transform initialTransform);
    C_Physics2d(
        Global* globalVariables, 
        myMath::Transform initialTransform,
        sf::Vector2f initialSpeed,
        double initialRotationSpeed);

    void process() override;

    myMath::Transform getTransform() override;


    sf::Vector2f getSpeed() { return speed; }
    double getRotationSpeed() { return rotationSpeed; }

    void setPosition(sf::Vector2f newPosition) { transform.position = newPosition; }
    void setRotation(double newRotation) { transform.rotation = newRotation; }
    void setSpeed(sf::Vector2f newSpeed) { speed = newSpeed; }
    void setRotationSpeed(double newRotationSpeed) { rotationSpeed = newRotationSpeed; }


    bool gravity = 0;

    myMath::Transform transform;

private:
    sf::Vector2f speed;
    double rotationSpeed = 0;

};

