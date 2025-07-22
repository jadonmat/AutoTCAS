#pragma once
#include "Engine.h"
//The goal of this class is to be able to set the direction(angle) of the aircraft



class Aileron : public Engine {

public:
    Aileron();

    sf::Angle getHeadingAngle() const;
    //getter to go from sf::Angle to float

    void setHeadingAngle(float angledegrees);

protected:
    sf::Angle deflectionangle;
    sf::Angle headingAngle;
};