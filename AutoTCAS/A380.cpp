#include "A380.h"

A380::A380() {}

//Airliner Shape
std::vector<sf::ConvexShape> A380::createAircraftShape(float scale) {
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
	fuselage.setPoint(0, sf::Vector2f(0.25f, -1.75f));
	fuselage.setPoint(1, sf::Vector2f(0.5f, -1.5f));
	fuselage.setPoint(2, sf::Vector2f(1.0f, -1.0f));
	fuselage.setPoint(3, sf::Vector2f(2.0f, 0.0f));
	fuselage.setPoint(4, sf::Vector2f(3.0f, 1.5f));
	fuselage.setPoint(5, sf::Vector2f(4.25f, 3.0f));
	fuselage.setPoint(6, sf::Vector2f(7.5f, 10.0f));
	fuselage.setPoint(7, sf::Vector2f(8.5f, 15.0f));
	fuselage.setPoint(8, sf::Vector2f(8.75f, 16.0f));
	fuselage.setPoint(9, sf::Vector2f(9.0f, 17.5f));
	fuselage.setPoint(10, sf::Vector2f(9.0f, 20.0f));
	fuselage.setPoint(11, sf::Vector2f(9.0f, 30.0f));

	fuselage.setPoint(12, sf::Vector2f(8.0f, 90.0f));
	fuselage.setPoint(13, sf::Vector2f(7.0f, 100.0f));

	fuselage.setPoint(14, sf::Vector2f(0.0f, 125.0f));

	fuselage.setPoint(15, sf::Vector2f(-8.0f, 100.0f));
	fuselage.setPoint(16, sf::Vector2f(-9.0f, 90.0f));

	fuselage.setPoint(17, sf::Vector2f(-9.0f, 30.0f));
	fuselage.setPoint(18, sf::Vector2f(-9.0f, 20.0f));
	fuselage.setPoint(19, sf::Vector2f(-9.0f, 17.5f));
	fuselage.setPoint(20, sf::Vector2f(-8.75f, 16.0f));
	fuselage.setPoint(21, sf::Vector2f(-8.5f, 15.0f));
	fuselage.setPoint(22, sf::Vector2f(-7.5f, 10.0f));
	fuselage.setPoint(23, sf::Vector2f(-4.25f, 3.0f));
	fuselage.setPoint(24, sf::Vector2f(-3.0f, 1.5f));
	fuselage.setPoint(25, sf::Vector2f(-2.0f, 0.0f));
	fuselage.setPoint(26, sf::Vector2f(-1.0f, -1.0f));
	fuselage.setPoint(27, sf::Vector2f(-0.5f, -1.5f));
	fuselage.setPoint(28, sf::Vector2f(0.25f, -1.75f));

	//tailoval
	float centerX = 0.0f; // Center of the oval
	float centerY = 60.0f;
	float radiusX = 4.0f; // Horizontal radius
	float radiusY = 10.0f;  // Vertical radius

	for (int i = 0; i < pointCount; ++i) {
		float angle = 2.0f * 3.14159265f * static_cast<float>(i) / static_cast<float>(pointCount);
		float x = centerX + std::cos(angle) * radiusX;
		float y = centerY + std::sin(angle) * radiusY;
		tailoval.setPoint(i, sf::Vector2f(x, y));
	}
	// right wing
	rightwing.setPoint(0, sf::Vector2f(0.0f, 32.5f));
	rightwing.setPoint(1, sf::Vector2f(65.0f, 81.0f));
	rightwing.setPoint(2, sf::Vector2f(65.5f, 81.5f));
	rightwing.setPoint(3, sf::Vector2f(66.0f, 82.0f));
	rightwing.setPoint(4, sf::Vector2f(66.5f, 83.0f));
	rightwing.setPoint(5, sf::Vector2f(67.5f, 87.5f));
	rightwing.setPoint(6, sf::Vector2f(5.0f, 62.5f));

	// Left wing
	leftwing.setPoint(0, sf::Vector2f(-5.0f, 32.5f));
	leftwing.setPoint(1, sf::Vector2f(-65.0f, 81.0f));
	leftwing.setPoint(2, sf::Vector2f(-65.5f, 81.5f));
	leftwing.setPoint(3, sf::Vector2f(-66.0f, 82.0f));
	leftwing.setPoint(4, sf::Vector2f(-66.5f, 83.0f));
	leftwing.setPoint(5, sf::Vector2f(-67.5f, 87.5f));
	leftwing.setPoint(6, sf::Vector2f(-5.0f, 62.5f));

	//Lower right tail
	righttail.setPoint(0, sf::Vector2f(5.0f, 100.0f));
	righttail.setPoint(1, sf::Vector2f(25.0f, 120.0f));
	righttail.setPoint(2, sf::Vector2f(25.5f, 120.5f));
	righttail.setPoint(3, sf::Vector2f(26.0f, 121.0f));
	righttail.setPoint(4, sf::Vector2f(26.5f, 122.0f));
	righttail.setPoint(5, sf::Vector2f(27.0f, 126.5f));
	righttail.setPoint(6, sf::Vector2f(27.25f, 130.0f));
	righttail.setPoint(7, sf::Vector2f(2.0f, 118.17f));

	//lower left tail
	lefttail.setPoint(0, sf::Vector2f(-5.0f, 100.0f));
	lefttail.setPoint(1, sf::Vector2f(-25.0f, 120.0f));
	lefttail.setPoint(2, sf::Vector2f(-25.5f, 120.5f));
	lefttail.setPoint(3, sf::Vector2f(-26.0f, 121.0f));
	lefttail.setPoint(4, sf::Vector2f(-26.5f, 122.0f));
	lefttail.setPoint(5, sf::Vector2f(-27.0f, 126.5f));
	lefttail.setPoint(6, sf::Vector2f(-27.25f, 130.0f));
	lefttail.setPoint(7, sf::Vector2f(-2.0f, 118.17f));

	// Right engine
	float diff1x = 0.0f;
	float diff1y = -13.0f;
	rightengine.setPoint(0, sf::Vector2f(21.0f + diff1x, 70.0f + diff1y));
	rightengine.setPoint(1, sf::Vector2f(21.0f + diff1x, 55.0f + diff1y));
	rightengine.setPoint(2, sf::Vector2f(22.0f + diff1x, 54.0f + diff1y));

	rightengine.setPoint(3, sf::Vector2f(25.0f + diff1x, 54.0f + diff1y));

	rightengine.setPoint(4, sf::Vector2f(28.0f + diff1x, 54.0f + diff1y));
	rightengine.setPoint(5, sf::Vector2f(29.0f + diff1x, 55.0f + diff1y));
	rightengine.setPoint(6, sf::Vector2f(29.0f + diff1x, 62.5f + diff1y));
	rightengine.setPoint(7, sf::Vector2f(27.5f + diff1x, 65.0f + diff1y));
	rightengine.setPoint(8, sf::Vector2f(25.0f + diff1x, 70.0f + diff1y));

	//rightengine2
	float diff2x = 5.0f;
	float diff2y = 3.95f;
	rightengine2.setPoint(0, sf::Vector2f(36.0f + diff2x, 70.0f + diff2y));
	rightengine2.setPoint(1, sf::Vector2f(36.0f + diff2x, 55.0f + diff2y));
	rightengine2.setPoint(2, sf::Vector2f(37.0f + diff2x, 54.0f + diff2y));

	rightengine2.setPoint(3, sf::Vector2f(40.0f + diff2x, 54.0f + diff2y));

	rightengine2.setPoint(4, sf::Vector2f(43.0f + diff2x, 54.0f + diff2y));
	rightengine2.setPoint(5, sf::Vector2f(44.0f + diff2x, 55.0f + diff2y));
	rightengine2.setPoint(6, sf::Vector2f(44.0f + diff2x, 62.5f + diff2y));
	rightengine2.setPoint(7, sf::Vector2f(42.5f + diff2x, 65.0f + diff2y));
	rightengine2.setPoint(8, sf::Vector2f(40.0f + diff2x, 70.0f + diff2y));


	//Left Engine
	leftengine.setPoint(0, sf::Vector2f(-21.0f + diff1x, 70.0f + diff1y));
	leftengine.setPoint(1, sf::Vector2f(-21.0f + diff1x, 55.0f + diff1y));
	leftengine.setPoint(2, sf::Vector2f(-22.0f + diff1x, 54.0f + diff1y));

	leftengine.setPoint(3, sf::Vector2f(-25.0f + diff1x, 54.0f + diff1y));

	leftengine.setPoint(4, sf::Vector2f(-28.0f + diff1x, 54.0f + diff1y));
	leftengine.setPoint(5, sf::Vector2f(-29.0f + diff1x, 55.0f + diff1y));
	leftengine.setPoint(6, sf::Vector2f(-29.0f + diff1x, 62.5f + diff1y));
	leftengine.setPoint(7, sf::Vector2f(-27.5f + diff1x, 65.0f + diff1y));
	leftengine.setPoint(8, sf::Vector2f(-25.0f + diff1x, 70.0f + diff1y));

	//leftengine2
	leftengine2.setPoint(0, sf::Vector2f(-36.0f - diff2x, 70.0f + diff2y));
	leftengine2.setPoint(1, sf::Vector2f(-36.0f - diff2x, 55.0f + diff2y));
	leftengine2.setPoint(2, sf::Vector2f(-37.0f - diff2x, 54.0f + diff2y));

	leftengine2.setPoint(3, sf::Vector2f(-40.0f - diff2x, 54.0f + diff2y));

	leftengine2.setPoint(4, sf::Vector2f(-43.0f - diff2x, 54.0f + diff2y));
	leftengine2.setPoint(5, sf::Vector2f(-44.0f - diff2x, 55.0f + diff2y));
	leftengine2.setPoint(6, sf::Vector2f(-44.0f - diff2x, 62.5f + diff2y));
	leftengine2.setPoint(7, sf::Vector2f(-42.5f - diff2x, 65.0f + diff2y));
	leftengine2.setPoint(8, sf::Vector2f(-40.0f - diff2x, 70.0f + diff2y));


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