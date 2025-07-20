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

    // Define default shape
   virtual std::vector<sf::ConvexShape> createAircraftShape(float scale) {
       std::vector<sf::ConvexShape> shapes;
       sf::ConvexShape plane;
        plane.setPointCount(2);
   
        plane.setPoint(0, sf::Vector2f(0, 0));
		plane.setPoint(1, sf::Vector2f(10, 20));

        //scale the size of the plane
        plane.setScale(sf::Vector2f(scale, scale));

        //set origin
        plane.setOrigin(plane.getGeometricCenter());

        //Setting color
        plane.setFillColor(sf::Color::Green);

		shapes.push_back(plane);
        return shapes;
    }

    //Getter and setters for ShapeScaling
    void setShapeScale(float scale) {
        ShapeScale = scale;
    }
    float getShapeScale() const {
        return ShapeScale;
    }


    //update the aircrafts position over time
    void update(sf::Time dt) {
        position.x += velocity.x * dt.asSeconds(); //convert dt to float from cf::Time
        position.y += velocity.y * dt.asSeconds();
    }

        void avoidCollision(const std::vector<Aircraft*>& aircrafts, sf::Time dt) {
            float deltaTime = dt.asSeconds();
            if (deltaTime <= 0.f) {
                return; // Skip if dt is invalid
            }

            // Find the closest aircraft
            float minDistance = warningrange; // Initialize to maximum detection range
            sf::Vector2f closestSeparation(0.f, 0.f);
            bool found = false;

            for (const auto& other : aircrafts) {
                if (other != this && DetectAircraft(other)) {
                    float distance = std::hypot(other->getPosition().x - position.x, other->getPosition().y - position.y);
                    if (distance > 0 && distance < minDistance) {
                        minDistance = distance;
                        closestSeparation = position - other->getPosition();
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
                float smoothingFactor = 0.05f; // Base turn speed
                float maxTurnRate = 0.065f; // Max degrees per second
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