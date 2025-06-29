#pragma once
#include "Aileron.h"

class Radar : public Aileron {
public:



    sf::Vector2f getPosition() const {
        return position;
    }

    void setPosition(sf::Vector2f pos) {
        position.x = pos.x;
        position.y = pos.y;
    }


protected:
    sf::Vector2f position;



};
