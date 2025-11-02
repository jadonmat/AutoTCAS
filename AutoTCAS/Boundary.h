#pragma once
#include <SFML/Graphics.hpp>
#include "Aircraft.h"
//#include "Events.h" OR
class Boundary {
public:
	Boundary();
void BoundaryInteraction(int i, sf::RenderWindow& window,
	std::vector<Aircraft*>& aircrafts, 
	std::vector<std::vector<sf::ConvexShape>>& aircraftShapes);


};