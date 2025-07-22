#include "Aileron.h"

Aileron::Aileron() {};

sf::Angle Aileron::getHeadingAngle() const {
    sf::Angle headingAngle = sf::degrees(std::atan2(getVelocity().y, getVelocity().x) * 180.0f / 3.14159265f);
    return headingAngle; //returns in degrees
}
//getter to go from sf::Angle to float


void Aileron::setHeadingAngle(float angledegrees) {
    float angleradians = angledegrees * (3.14159265f / 180.0f);
    float speed = std::sqrt(getVelocity().x * getVelocity().x + getVelocity().y * getVelocity().y);
    velocity = sf::Vector2f(std::cos(angleradians), std::sin(angleradians)) * speed;
    sf::Angle headingAngle = sf::degrees(std::atan2(getVelocity().y, getVelocity().x) * 180.0f / 3.14159265f);
}