#include <iostream>
#include "Boundary.h"
using namespace std;

Boundary::Boundary() {}

void Boundary::BoundaryInteraction(int i, sf::RenderWindow& window, 
    std::vector<Aircraft*>& aircrafts, 
    std::vector<std::vector<sf::ConvexShape>>& aircraftShapes) {

    // Boundary interactions (Now integrated with aileron class)
    sf::Vector2f pos = aircrafts[i]->getPosition();
    sf::Vector2f vel = aircrafts[i]->getVelocity();
    bool updated = false;
    if (pos.x > static_cast<float>(window.getSize().x)) {
        pos.x = static_cast<float>(window.getSize().x);
        vel.x = -vel.x;
        aircrafts[i]->setVelocity(vel);
        updated = true;
    }
    else if (pos.x < 0.0f) {
        pos.x = 0.0f;
        vel.x = -vel.x;
        aircrafts[i]->setVelocity(vel);
        updated = true;
    }
    else if (pos.y < 0.0f) {
        pos.y = 0.0f;
        vel.y = -vel.y;
        aircrafts[i]->setVelocity(vel);
        updated = true;
    }
    else if (pos.y > static_cast<float>(window.getSize().y)) {
        pos.y = static_cast<float>(window.getSize().y);
        vel.y = -vel.y;
        aircrafts[i]->setVelocity(vel);
        updated = true;
    }
    //ensures pos and vel are updated
    //aircrafts[i].setPosition(pos);
    //aircrafts[i].setVelocity(vel);

    if (updated) {
        float speed = std::sqrt(vel.x * vel.x + vel.y * vel.y);
        if (speed > 0.001f) { // Avoid updating heading for near-zero velocity
            float angleRadians = std::atan2(vel.y, vel.x);
            float angleDegrees = angleRadians * (180.0f / 3.14159265f);
            aircrafts[i]->setHeadingAngle(angleDegrees);
        }
    }

    //just in case out of bounds (deletion)
    if (pos.x - aircrafts[i]->getRange() > static_cast<float>(window.getSize().x)) {

        aircrafts.erase(aircrafts.begin() + i);
        aircraftShapes.erase(aircraftShapes.begin() + i);
        cout << "Out of bounds Aircraft Deleted" << endl;
    }
    else if (pos.x + aircrafts[i]->getRange() < 0.0f) {

        aircrafts.erase(aircrafts.begin() + i);
        aircraftShapes.erase(aircraftShapes.begin() + i);
        cout << "Out of bounds Aircraft Deleted" << endl;
    }
    else if (pos.y - aircrafts[i]->getRange() > static_cast<float>(window.getSize().y)) {

        aircrafts.erase(aircrafts.begin() + i);
        aircraftShapes.erase(aircraftShapes.begin() + i);
        cout << "Out of bounds Aircraft Deleted" << endl;
    }
    else if (pos.y + aircrafts[i]->getRange() < 0.0f) {

        aircrafts.erase(aircrafts.begin() + i);
        aircraftShapes.erase(aircraftShapes.begin() + i);
        cout << "Out of bounds Aircraft Deleted" << endl;
    }
}