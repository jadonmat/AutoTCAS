#pragma once
#include "Aircraft.h"

class A380 : public Aircraft {
public:
	A380() {}

    //Airliner Shape
	virtual std::vector<sf::ConvexShape> createA380Shape(float scale) {
		std::vector<sf::ConvexShape> shapes; //vector to hold the shapes
		sf::ConvexShape fuselage;
		sf::ConvexShape tailoval;
		const int pointCount = 32;
		tailoval.setPointCount(pointCount);
		sf::ConvexShape rightwing;
		sf::ConvexShape leftwing;
		sf::ConvexShape righttail;
		sf::ConvexShape lefttail;
		sf::ConvexShape rightengine;
		sf::ConvexShape rightengine2;
		sf::ConvexShape leftengine;
		sf::ConvexShape leftengine2;

		sf::ConvexShape rightaileron;
		sf::ConvexShape leftaileron;
		fuselage.setPointCount(29);
		rightwing.setPointCount(7);
		leftwing.setPointCount(7);
		righttail.setPointCount(8);
		lefttail.setPointCount(8);
		rightengine.setPointCount(9);
		rightengine2.setPointCount(9);
		leftengine.setPointCount(9);
		leftengine2.setPointCount(9);
		//rightaileron.setPointCount(4);
		//leftaileron.setPointCount(4);

		//fuselage
		fuselage.setPoint(0, sf::Vector2f(.25, -1.75));
		fuselage.setPoint(1, sf::Vector2f(0.5, -1.5));
		fuselage.setPoint(2, sf::Vector2f(1, -1));
		fuselage.setPoint(3, sf::Vector2f(2, 0));
		fuselage.setPoint(4, sf::Vector2f(3, 1.5));
		fuselage.setPoint(5, sf::Vector2f(4.25, 3));
		fuselage.setPoint(6, sf::Vector2f(7.5, 10));
		fuselage.setPoint(7, sf::Vector2f(8.5, 15));
		fuselage.setPoint(8, sf::Vector2f(8.75, 16));
		fuselage.setPoint(9, sf::Vector2f(9, 17.5));
		fuselage.setPoint(10, sf::Vector2f(9, 20));
		fuselage.setPoint(11, sf::Vector2f(9, 30));

		fuselage.setPoint(12, sf::Vector2f(8, 90));
		fuselage.setPoint(13, sf::Vector2f(7, 100));

		fuselage.setPoint(14, sf::Vector2f(0, 125));

		fuselage.setPoint(15, sf::Vector2f(-8, 100));
		fuselage.setPoint(16, sf::Vector2f(-9, 90));

		fuselage.setPoint(17, sf::Vector2f(-9, 30));
		fuselage.setPoint(18, sf::Vector2f(-9, 20));
		fuselage.setPoint(19, sf::Vector2f(-9, 17.5));
		fuselage.setPoint(20, sf::Vector2f(-8.75, 16));
		fuselage.setPoint(21, sf::Vector2f(-8.5, 15));
		fuselage.setPoint(22, sf::Vector2f(-7.5, 10));
		fuselage.setPoint(23, sf::Vector2f(-4.25, 3));
		fuselage.setPoint(24, sf::Vector2f(-3, 1.5));
		fuselage.setPoint(25, sf::Vector2f(-2, 0));
		fuselage.setPoint(26, sf::Vector2f(-1, -1));
		fuselage.setPoint(27, sf::Vector2f(-0.5, -1.5));
		fuselage.setPoint(28, sf::Vector2f(.25, -1.75));

		//tailoval
		float centerX = 0.f; // Center of the oval
		float centerY = 60.f;
		float radiusX = 4.f; // Horizontal radius
		float radiusY = 10.0f;  // Vertical radius

		for (int i = 0; i < pointCount; ++i) {
			float angle = 2 * 3.14159265f * i / pointCount;
			float x = centerX + std::cos(angle) * radiusX;
			float y = centerY + std::sin(angle) * radiusY;
			tailoval.setPoint(i, sf::Vector2f(x, y));
		}
	
		// right wing
		rightwing.setPoint(0, sf::Vector2f(0, 32.5));
		rightwing.setPoint(1, sf::Vector2f(65, 81));
		rightwing.setPoint(2, sf::Vector2f(65.5,81.5));
		rightwing.setPoint(3, sf::Vector2f(66, 82));
		rightwing.setPoint(4, sf::Vector2f(66.5, 83));
		rightwing.setPoint(5, sf::Vector2f(67.5, 87.5));
		rightwing.setPoint(6, sf::Vector2f(5, 62.5));

		// Left wing
		leftwing.setPoint(0, sf::Vector2f(-5, 32.5));
		leftwing.setPoint(1, sf::Vector2f(-65, 81));
		leftwing.setPoint(2, sf::Vector2f(-65.5, 81.5));
		leftwing.setPoint(3, sf::Vector2f(-66, 82));
		leftwing.setPoint(4, sf::Vector2f(-66.5, 83));
		leftwing.setPoint(5, sf::Vector2f(-67.5, 87.5));
		leftwing.setPoint(6, sf::Vector2f(-5, 62.5));

		//Lower right tail
		righttail.setPoint(0, sf::Vector2f(5, 100));
		righttail.setPoint(1, sf::Vector2f(25, 120));
		righttail.setPoint(2, sf::Vector2f(25.5, 120.5));
		righttail.setPoint(3, sf::Vector2f(26, 121));
		righttail.setPoint(4, sf::Vector2f(26.5, 122));
		righttail.setPoint(5, sf::Vector2f(27, 126.5));
		righttail.setPoint(6, sf::Vector2f(27.25, 130));
		righttail.setPoint(7, sf::Vector2f(2, 118.17));

		//lower left tail
		lefttail.setPoint(0, sf::Vector2f(-5, 100));
		lefttail.setPoint(1, sf::Vector2f(-25, 120));
		lefttail.setPoint(2, sf::Vector2f(-25.5, 120.5));
		lefttail.setPoint(3, sf::Vector2f(-26, 121));
		lefttail.setPoint(4, sf::Vector2f(-26.5, 122));
		lefttail.setPoint(5, sf::Vector2f(-27, 126.5));
		lefttail.setPoint(6, sf::Vector2f(-27.25, 130));
		lefttail.setPoint(7, sf::Vector2f(-2, 118.17));

		// Right engine
		int diff1x = 0;
		int diff1y = -13;
		rightengine.setPoint(0, sf::Vector2f(21 + diff1x, 70 + diff1y));
		rightengine.setPoint(1, sf::Vector2f(21 + diff1x, 55 + diff1y));
		rightengine.setPoint(2, sf::Vector2f(22 + diff1x, 54 + diff1y));

		rightengine.setPoint(3, sf::Vector2f(25 + diff1x, 54 + diff1y));

		rightengine.setPoint(4, sf::Vector2f(28 + diff1x, 54 + diff1y));
		rightengine.setPoint(5, sf::Vector2f(29 + diff1x, 55 + diff1y));
		rightengine.setPoint(6, sf::Vector2f(29 + diff1x, 62.5 + diff1y));
		rightengine.setPoint(7, sf::Vector2f(27.5 + diff1x, 65 + diff1y));
		rightengine.setPoint(8, sf::Vector2f(25 + diff1x, 70 + diff1y));

		//rightengine2
		int diff2x = 5;
		int diff2y = 3.95;
		rightengine2.setPoint(0, sf::Vector2f(36 + diff2x, 70 + diff2y));
		rightengine2.setPoint(1, sf::Vector2f(36 + diff2x, 55 + diff2y));
		rightengine2.setPoint(2, sf::Vector2f(37 + diff2x, 54 + diff2y));

		rightengine2.setPoint(3, sf::Vector2f(40 + diff2x, 54 + diff2y));

		rightengine2.setPoint(4, sf::Vector2f(43 + diff2x, 54 + diff2y));
		rightengine2.setPoint(5, sf::Vector2f(44 + diff2x, 55 + diff2y));
		rightengine2.setPoint(6, sf::Vector2f(44 + diff2x, 62.5 + diff2y));
		rightengine2.setPoint(7, sf::Vector2f(42.5 + diff2x, 65 + diff2y));
		rightengine2.setPoint(8, sf::Vector2f(40 + diff2x, 70 + diff2y));


		//Left Engine
		leftengine.setPoint(0, sf::Vector2f(-21 + diff1x, 70 + diff1y));
		leftengine.setPoint(1, sf::Vector2f(-21 + diff1x, 55 + diff1y));
		leftengine.setPoint(2, sf::Vector2f(-22 + diff1x, 54 + diff1y));

		leftengine.setPoint(3, sf::Vector2f(-25 + diff1x, 54 + diff1y));

		leftengine.setPoint(4, sf::Vector2f(-28 + diff1x, 54 + diff1y));
		leftengine.setPoint(5, sf::Vector2f(-29 + diff1x, 55 + diff1y));
		leftengine.setPoint(6, sf::Vector2f(-29 + diff1x, 62.5 + diff1y));
		leftengine.setPoint(7, sf::Vector2f(-27.5 + diff1x, 65 + diff1y));
		leftengine.setPoint(8, sf::Vector2f(-25 + diff1x, 70 + diff1y));

		//leftengine2
		leftengine2.setPoint(0, sf::Vector2f(-36 - diff2x, 70 + diff2y));
		leftengine2.setPoint(1, sf::Vector2f(-36 - diff2x, 55 + diff2y));
		leftengine2.setPoint(2, sf::Vector2f(-37 - diff2x, 54 + diff2y));

		leftengine2.setPoint(3, sf::Vector2f(-40 - diff2x, 54 + diff2y));

		leftengine2.setPoint(4, sf::Vector2f(-43 - diff2x, 54 + diff2y));
		leftengine2.setPoint(5, sf::Vector2f(-44 - diff2x, 55 + diff2y));
		leftengine2.setPoint(6, sf::Vector2f(-44 - diff2x, 62.5 + diff2y));
		leftengine2.setPoint(7, sf::Vector2f(-42.5 - diff2x, 65 + diff2y));
		leftengine2.setPoint(8, sf::Vector2f(-40 - diff2x, 70 + diff2y));


		//scale the size of the plane
		fuselage.setScale(sf::Vector2f(scale, scale));
		tailoval.setScale(sf::Vector2f(scale, scale));
		rightwing.setScale(sf::Vector2f(scale, scale));
		leftwing.setScale(sf::Vector2f(scale, scale));
		righttail.setScale(sf::Vector2f(scale, scale));
		lefttail.setScale(sf::Vector2f(scale, scale));
		rightengine.setScale(sf::Vector2f(scale, scale));
		rightengine2.setScale(sf::Vector2f(scale, scale));
		leftengine.setScale(sf::Vector2f(scale, scale));
		leftengine2.setScale(sf::Vector2f(scale, scale));
		rightaileron.setScale(sf::Vector2f(scale, scale));
		leftaileron.setScale(sf::Vector2f(scale, scale));


		//set origin
		fuselage.setOrigin(fuselage.getGeometricCenter());
		//tailoval.setOrigin(tailoval.getGeometricCenter());
		rightwing.setOrigin(fuselage.getGeometricCenter());
		leftwing.setOrigin(fuselage.getGeometricCenter());
		righttail.setOrigin(fuselage.getGeometricCenter());
		lefttail.setOrigin(fuselage.getGeometricCenter());
		rightengine.setOrigin(fuselage.getGeometricCenter());
		rightengine2.setOrigin(fuselage.getGeometricCenter());
		leftengine.setOrigin(fuselage.getGeometricCenter());
		leftengine2.setOrigin(fuselage.getGeometricCenter());
		rightaileron.setOrigin(fuselage.getGeometricCenter());
		leftaileron.setOrigin(fuselage.getGeometricCenter());

		//Setting color
		fuselage.setFillColor(sf::Color::Green);
		tailoval.setFillColor(sf::Color::Green);
		rightwing.setFillColor(sf::Color::Green);
		leftwing.setFillColor(sf::Color::Green);
		righttail.setFillColor(sf::Color::Green);
		lefttail.setFillColor(sf::Color::Green);
		rightengine.setFillColor(sf::Color::Green);
		rightengine2.setFillColor(sf::Color::Green);
		leftengine.setFillColor(sf::Color::Green);
		leftengine2.setFillColor(sf::Color::Green);
		rightaileron.setFillColor(sf::Color::Green);
		leftaileron.setFillColor(sf::Color::Green);



		shapes.push_back(fuselage);
		shapes.push_back(tailoval);
		shapes.push_back(rightwing);
		shapes.push_back(leftwing);
		shapes.push_back(righttail);
		shapes.push_back(lefttail);
		shapes.push_back(rightengine);
		shapes.push_back(rightengine2);
		shapes.push_back(leftengine);
		shapes.push_back(leftengine2);
		//shapes.push_back(rightaileron);
		//shapes.push_back(leftaileron);



		return shapes;
	}


};