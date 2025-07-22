// ABSTRACT BASE CLASS FOR AIRCRAFT
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
    Aircraft();//default constructor
    ~Aircraft();//deconstructor

    // Define default shape
    virtual std::vector<sf::ConvexShape> createAircraftShape(float scale) = 0; // defines the abstract base class

    //Getter and setters for ShapeScaling
    void setShapeScale(float scale);
    float getShapeScale() const;


    //update the aircrafts position over time
    void update(sf::Time dt);

    void avoidCollision(int i, sf::RenderWindow& window, const std::vector<Aircraft*>& aircrafts, std::vector<std::vector<sf::ConvexShape>>& aircraftShapes,
        sf::Time dt, float smoothingFactor, float maxTurnRate);

protected:
    float ShapeScale;
};