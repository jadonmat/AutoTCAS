#pragma once
#include "Aircraft.h"

class Airliner : public Aircraft {
public:
	Airliner() {}

    virtual sf::ConvexShape createAircraftShape(float scale) {
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



};