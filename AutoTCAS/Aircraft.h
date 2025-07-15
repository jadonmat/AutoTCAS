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
    Aircraft() { ShapeScale = 0.26f; }//default constructor
    ~Aircraft() {}//deconstructor

    // define shape (Change to Airliner Shape in own class later)
    sf::ConvexShape createAircraftShape(float scale) {
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
        plane.setScale(sf::Vector2f(scale, scale)); //(0.5 = half size)
        //set origin
        plane.setOrigin(plane.getGeometricCenter());

        //Setting color
        plane.setFillColor(sf::Color::Green);

        return plane;
    }

    //Getter and setters for ShapeScaling
    void setShapeScale(float scale) {
        ShapeScale = scale;
    }
    float getShapeScale() {
        return ShapeScale;
    }


    //update the aircrafts position over time
    void update(sf::Time dt) {
        position.x += velocity.x * dt.asSeconds(); //convert dt to float from cf::Time
        position.y += velocity.y * dt.asSeconds();
    }

        void avoidCollision(const std::vector<Aircraft>& aircrafts, sf::Time dt) {
            float deltaTime = dt.asSeconds();
            if (deltaTime <= 0.f) {
                return; // Skip if dt is invalid
            }

            // Find the closest aircraft
            float minDistance = warningrange; // Initialize to maximum detection range
            sf::Vector2f closestSeparation(0.f, 0.f);
            bool found = false;

            for (const auto& other : aircrafts) {
                if (&other != this && DetectAircraft(other)) {
                    float distance = std::hypot(other.getPosition().x - position.x, other.getPosition().y - position.y);
                    if (distance > 0 && distance < minDistance) {
                        minDistance = distance;
                        closestSeparation = position - other.getPosition();
                        found = true;
                    }
                }
            }

            if (found) {
                // Normalize the separation vector
                float currentDistance = std::sqrt(closestSeparation.x * closestSeparation.x + closestSeparation.y * closestSeparation.y);
                if (currentDistance < 0.001f) {
                    currentDistance = 0.001f;
                }
                if (std::abs(closestSeparation.x) < 0.001f && std::abs(closestSeparation.y) < 0.001f) {
                    return; // Skip if separation is effectively zero
                }
                closestSeparation.x /= currentDistance;
                closestSeparation.y /= currentDistance;

                // Apply separation weight based on proximity
                float separationWeight = (warningrange - minDistance) / warningrange;
                closestSeparation.x *= separationWeight;
                closestSeparation.y *= separationWeight;

                // Calculate desired heading
                float desiredAngleRadians = std::atan2(closestSeparation.y, closestSeparation.x);
                float desiredAngleDegrees = desiredAngleRadians * (180.0f / 3.14f);

                // relative position and velocity for additional checks
                // 
                //sf::Vector2f relativePos = -closestSeparation; // other.getPosition() - position
                //sf::Vector2f relativeVelocity = other.getVelocity() - getVelocity();
                //float crossProduct = closestSeparation.x * relativePos.y - closestSeparation.y * relativePos.x;
                //float closingSpeed = relativeVelocity.x * closestSeparation.x + relativeVelocity.y * closestSeparation.y;

                float currentAngle = getHeadingAngle().asDegrees();
                float angleDiff = desiredAngleDegrees - currentAngle;

                // Normalize angle difference
                while (angleDiff > 180) {
                    angleDiff -= 360;
                }
                while (angleDiff < -180) {
                    angleDiff += 360;
                }

                // Apply smooth turning
                float smoothingFactor = 0.0125f; // Base turn speed
                float maxTurnRate = 0.125f; // Max degrees per second
                float angleChange = std::clamp(smoothingFactor * angleDiff * deltaTime,
                    -maxTurnRate * deltaTime, maxTurnRate * deltaTime);
                float newAngle = currentAngle + angleChange;
                headingAngle = sf::degrees(newAngle);
                setHeadingAngle(newAngle);
                //std::cout << "Turn rate: " << angleChange / deltaTime << " deg/s, angleDiff: " << angleDiff << std::endl;
            }
        }

protected:
    float ShapeScale;
};