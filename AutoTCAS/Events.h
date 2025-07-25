#pragma once
#include "UI.h"
#include "Aircraft.h"
#include "A380.h"

class Events {
public:
	Events();
	// Function to handle events
	void handleEvents(sf::RenderWindow& window, std::vector<Aircraft*>& aircrafts, 
		std::vector<std::vector<sf::ConvexShape>>& aircraftShapes, UI& ui, sf::Text& clickText, sf::Text& fpsText, sf::Text& reset);

	sf::Vector2f mousePos;
private:
};