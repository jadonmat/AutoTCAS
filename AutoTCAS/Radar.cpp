#include "Radar.h"

Radar::Radar() {};


sf::Vector2f Radar::getPosition() const {
    return position;
}

void Radar::setPosition(sf::Vector2f pos) {
    position.x = pos.x;
    position.y = pos.y;
}