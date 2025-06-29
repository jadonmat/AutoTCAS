#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "TCAS.h"

//Vector2i is used for a vector of ints
//Vector2f is used for a vector of floats
//etc

//Do not use SFML's angle class in setheadingangle, doesnt work with std trig functions

class Aircraft :public TCAS {
public:
    Aircraft() {}//default constructor
    ~Aircraft() {}//deconstructor

    // define shape
    sf::ConvexShape createAircraftShape() {
        sf::ConvexShape plane;
        plane.setPointCount(32);
        //first half
        plane.setPoint(0, sf::Vector2f(0, 0));
        plane.setPoint(1, sf::Vector2f(2, .75));
        plane.setPoint(2, sf::Vector2f(4, 1.5));
        plane.setPoint(3, sf::Vector2f(6.25, 2.5));
        plane.setPoint(4, sf::Vector2f(7.5, 5));
        plane.setPoint(5, sf::Vector2f(8.5, 15));
        plane.setPoint(6, sf::Vector2f(8.75, 16));
        plane.setPoint(7, sf::Vector2f(9, 17.5));
        plane.setPoint(8, sf::Vector2f(9, 20));
        plane.setPoint(9, sf::Vector2f(9, 30));
        plane.setPoint(10, sf::Vector2f(30, 50));
        plane.setPoint(11, sf::Vector2f(30, 65));
        plane.setPoint(12, sf::Vector2f(9, 45));
        plane.setPoint(13, sf::Vector2f(9, 80));
        plane.setPoint(14, sf::Vector2f(15, 80));
        plane.setPoint(15, sf::Vector2f(15, 95));
        //intersection
        plane.setPoint(16, sf::Vector2f(0, 82));
        //second half
        plane.setPoint(17, sf::Vector2f(-15, 95));
        plane.setPoint(18, sf::Vector2f(-15, 80));
        plane.setPoint(19, sf::Vector2f(-9, 80));
        plane.setPoint(20, sf::Vector2f(-9, 45));
        plane.setPoint(21, sf::Vector2f(-30, 65));
        plane.setPoint(22, sf::Vector2f(-30, 50));
        plane.setPoint(23, sf::Vector2f(-9, 30));
        plane.setPoint(24, sf::Vector2f(-9, 20));
        plane.setPoint(25, sf::Vector2f(-9, 17.5));
        plane.setPoint(26, sf::Vector2f(-8.75, 16));
        plane.setPoint(27, sf::Vector2f(-8.5, 15));
        plane.setPoint(28, sf::Vector2f(-7.5, 5));
        plane.setPoint(29, sf::Vector2f(-6.25, 2.5));
        plane.setPoint(30, sf::Vector2f(-4, 1.5));
        plane.setPoint(31, sf::Vector2f(-2, .75));
        //scale the size of the plane
        plane.setScale(sf::Vector2f(0.5, 0.5)); //(0.5 = half size)
        //set origin
        plane.setOrigin(plane.getGeometricCenter());

        //Setting color
        plane.setFillColor(sf::Color::Green);

        return plane;
    }


    //update the aircrafts position over time
    void update(sf::Time dt) {
        position.x += velocity.x * dt.asSeconds(); //convert dt to float from cf::Time
        position.y += velocity.y * dt.asSeconds();
    }

    void avoidCollision(const std::vector<Aircraft>& aircrafts, sf::Time dt) {
        float deltaTime = dt.asSeconds();
        for (const auto& other : aircrafts) { //loop over aircraft vector using auto instead of nested fl
            if (&other != this && detectAircraft(other)) { //ensures that the next aircraft is being compared
                float distance = std::hypot(other.getPosition().x - position.x, other.getPosition().y - position.y);

                if (distance > 0 && distance < range) {

                    sf::Vector2f separation = position - other.getPosition();// determines direction the other plane should seperate

                    float currentDistance = std::sqrt(separation.x * separation.x + separation.y * separation.y); //determines distance betwen planes

                    if (currentDistance < 0.001f) {
                        currentDistance = 0.001f;
                    }
                    //Normalize x and y distance
                    separation.x /= currentDistance;
                    separation.y /= currentDistance;


                    float separationWeight = (range - distance) / range; //weighted seperation distance

                    // Scale the separation vector -- tweak the multiplier to control force strength
                    separation.x *= separationWeight;
                    separation.y *= separationWeight;


                    float desiredAngleRadians = std::atan2(separation.y, separation.x);//determines the heading angle
                    float desiredAngleDegrees = desiredAngleRadians * (180.0f / 3.14f);

                    sf::Vector2f relativePos = other.getPosition() - position;
                    sf::Vector2f relativeVelocity = other.getVelocity() - getVelocity();
                    float crossProduct = separation.x * relativePos.y - separation.y * relativePos.x;
                    float closingSpeed = relativeVelocity.x * separation.x + relativeVelocity.y * separation.y;

                    float currentAngle = headingAngle.asDegrees();
                    float angleDiff = desiredAngleDegrees - currentAngle;

                    while (angleDiff > 180) {
                        angleDiff -= 360; //Normalizes the angle difference to be between -180 and 180
                    }
                    while (angleDiff < -180) {
                        angleDiff += 360;
                    }

                    float smoothingFactor = 1.f; // Base turn speed
                    float maxTurnRate = 5.0f; // Max degrees per second
                    float angleChange = std::clamp(smoothingFactor * angleDiff * deltaTime,
                        -maxTurnRate * deltaTime, maxTurnRate * deltaTime);
                    float newAngle = currentAngle + angleChange; //calcualating new angle
                    headingAngle = sf::degrees(newAngle);//updating heading angle
                    setHeadingAngle(newAngle);
                }
            }
        }
    }
};