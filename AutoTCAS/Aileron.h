#pragma once
#include "Engine.h"
//The goal of this class is to be able to set the direction(angle) of the aircraft



class Aileron : public Engine {

public:
    Aileron() {};

    sf::Angle getHeadingAngle() const {
        sf::Angle headingAngle = sf::degrees(std::atan2(getVelocity().y, getVelocity().x) * 180 / 3.14159265);
        return headingAngle; //returns in degrees
    }
    //getter to go from sf::Angle to float


    void setHeadingAngle(float angledegrees) {
        float angleradians = angledegrees * (3.14159265 / 180);
        float speed = std::sqrt(getVelocity().x * getVelocity().x + getVelocity().y * getVelocity().y);
        velocity = sf::Vector2f(std::cos(angleradians), std::sin(angleradians)) * speed;
    }

protected:
    sf::Angle deflectionangle;
    sf::Angle headingAngle;
};