#pragma once
#include "Engine.h"
//The goal of this class is to be able to set the direction(angle) of the aircraft



class Aileron : public Engine {

public:
    Aileron() {};

    sf::Angle getHeadingAngle() const {
        sf::Angle headingAngle = sf::degrees(std::atan2(getVelocity().y, getVelocity().x) * 180.0f / 3.14159265f);
        return headingAngle; //returns in degrees
    }
    //getter to go from sf::Angle to float


    void setHeadingAngle(float angledegrees) {
        float angleradians = angledegrees * (3.14159265f / 180.0f);
        float speed = std::sqrt(getVelocity().x * getVelocity().x + getVelocity().y * getVelocity().y);
        velocity = sf::Vector2f(std::cos(angleradians), std::sin(angleradians)) * speed;
        sf::Angle headingAngle = sf::degrees(std::atan2(getVelocity().y, getVelocity().x) * 180.0f / 3.14159265f);
    }

protected:
    sf::Angle deflectionangle;
    sf::Angle headingAngle;
};