#pragma once
#include "Aircraft.h"

class A380 : public Aircraft {
public:
	A380();

    //Airliner Shape
	std::vector<sf::ConvexShape> createAircraftShape(float scale);
};