#pragma once
#include "Aileron.h"

class Radar : public Aileron {
public:
    Radar();

    sf::Vector2f getPosition() const;

    void setPosition(sf::Vector2f pos);


protected:
    sf::Vector2f position;



};
