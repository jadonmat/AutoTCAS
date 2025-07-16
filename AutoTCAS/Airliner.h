#pragma once
#include "Aircraft.h"

class Airliner : public Aircraft {
public:
	Airliner() {}

    //Airliner Shape
	virtual std::vector<sf::ConvexShape> createAircraftShape(float scale) {
		std::vector<sf::ConvexShape> shapes; //vector to hold the shapes
		sf::ConvexShape fuselage;
		sf::ConvexShape rightwing;
		sf::ConvexShape leftwing;
		sf::ConvexShape righttail;
		sf::ConvexShape lefttail;
		sf::ConvexShape rightengine;
		sf::ConvexShape leftengine;
		sf::ConvexShape rightaileron;
		sf::ConvexShape leftaileron;
		fuselage.setPointCount(27);
		rightwing.setPointCount(4);
		leftwing.setPointCount(4);
		righttail.setPointCount(4);
		lefttail.setPointCount(4);

		//fuselage
		fuselage.setPoint(0, sf::Vector2f(.5, -2.5));
		fuselage.setPoint(1, sf::Vector2f(.75, -2));
		fuselage.setPoint(2, sf::Vector2f(1, -1));
		fuselage.setPoint(3, sf::Vector2f(2, 0));
		fuselage.setPoint(4, sf::Vector2f(3, 1.5));
		fuselage.setPoint(5, sf::Vector2f(4.25, 2.5));
		fuselage.setPoint(6, sf::Vector2f(7.5, 10));
		fuselage.setPoint(7, sf::Vector2f(8.5, 15));
		fuselage.setPoint(8, sf::Vector2f(8.75, 16));
		fuselage.setPoint(9, sf::Vector2f(9, 17.5));
		fuselage.setPoint(10, sf::Vector2f(9, 20));
		fuselage.setPoint(11, sf::Vector2f(9, 30));
		fuselage.setPoint(12, sf::Vector2f(9, 105));

		fuselage.setPoint(13, sf::Vector2f(0, 125));

		fuselage.setPoint(14, sf::Vector2f(-9, 105));
		fuselage.setPoint(15, sf::Vector2f(-9, 30));
		fuselage.setPoint(16, sf::Vector2f(-9, 20));
		fuselage.setPoint(17, sf::Vector2f(-9, 17.5));
		fuselage.setPoint(18, sf::Vector2f(-8.75, 16));
		fuselage.setPoint(19, sf::Vector2f(-8.5, 15));
		fuselage.setPoint(20, sf::Vector2f(-7.5, 10));
		fuselage.setPoint(21, sf::Vector2f(-4.25, 2.5));
		fuselage.setPoint(22, sf::Vector2f(-3, 1.5));
		fuselage.setPoint(23, sf::Vector2f(-2, 0));
		fuselage.setPoint(24, sf::Vector2f(-1, -1));
		fuselage.setPoint(25, sf::Vector2f(-.75, -2));
		fuselage.setPoint(26, sf::Vector2f(-.5, -2.5));
	
		// right wing
		rightwing.setPoint(0, sf::Vector2f(5, 40));
		rightwing.setPoint(1, sf::Vector2f(50, 85));
		rightwing.setPoint(2, sf::Vector2f(52.5, 95));
		rightwing.setPoint(3, sf::Vector2f(5, 70));

		// Left wing
		leftwing.setPoint(0, sf::Vector2f(-5, 70));
		leftwing.setPoint(1, sf::Vector2f(-52.5, 100));
		leftwing.setPoint(2, sf::Vector2f(-50, 90));
		leftwing.setPoint(3, sf::Vector2f(-5, 40));



		//Lower right tail
		righttail.setPoint(0, sf::Vector2f(5, 100));
		righttail.setPoint(1, sf::Vector2f(25, 120));
		righttail.setPoint(2, sf::Vector2f(27.25, 130));
		righttail.setPoint(3, sf::Vector2f(5, 118.17));


		//lower left tail
		lefttail.setPoint(0, sf::Vector2f(-5, 118.17));
		lefttail.setPoint(1, sf::Vector2f(-27.25, 130));
		lefttail.setPoint(2, sf::Vector2f(-25, 120));
		lefttail.setPoint(3, sf::Vector2f(-5, 100));






		//scale the size of the plane
		fuselage.setScale(sf::Vector2f(scale, scale));
		rightwing.setScale(sf::Vector2f(scale, scale));
		leftwing.setScale(sf::Vector2f(scale, scale));
		righttail.setScale(sf::Vector2f(scale, scale));
		lefttail.setScale(sf::Vector2f(scale, scale));
		//rightengine.setScale(sf::Vector2f(scale, scale));
		//leftengine.setScale(sf::Vector2f(scale, scale));
		//rightaileron.setScale(sf::Vector2f(scale, scale));
		//leftaileron.setScale(sf::Vector2f(scale, scale));


		//set origin
		fuselage.setOrigin(fuselage.getGeometricCenter());
		rightwing.setOrigin(fuselage.getGeometricCenter());
		leftwing.setOrigin(fuselage.getGeometricCenter());
		righttail.setOrigin(fuselage.getGeometricCenter());
		lefttail.setOrigin(fuselage.getGeometricCenter());
		//rightengine.setOrigin(fuselage.getGeometricCenter());
		//leftengine.setOrigin(fuselage.getGeometricCenter());
		//rightaileron.setOrigin(fuselage.getGeometricCenter());
		//leftaileron.setOrigin(fuselage.getGeometricCenter());

		//Setting color
		fuselage.setFillColor(sf::Color::Green);
		rightwing.setFillColor(sf::Color::Green);
		leftwing.setFillColor(sf::Color::Green);
		righttail.setFillColor(sf::Color::Green);
		lefttail.setFillColor(sf::Color::Green);
		//rightengine.setFillColor(sf::Color::Green);
		//leftengine.setFillColor(sf::Color::Green);
		//rightaileron.setFillColor(sf::Color::Green);
		//leftaileron.setFillColor(sf::Color::Green);



		shapes.push_back(fuselage);
		shapes.push_back(rightwing);
		shapes.push_back(leftwing);
		shapes.push_back(righttail);
		shapes.push_back(lefttail);
		//shapes.push_back(rightengine);
		//shapes.push_back(leftengine);
		//shapes.push_back(rightaileron);
		//shapes.push_back(leftaileron);


		return shapes;
	}


};