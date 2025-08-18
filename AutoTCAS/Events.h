#pragma once
#include "UI.h"
#include "Aircraft.h"
#include "A380.h"

class Events {
public:
	Events();
	// Function to handle events
	void handleEvents(sf::RenderWindow& window, std::vector<Aircraft*>& aircrafts,
		std::vector<std::vector<sf::ConvexShape>>& aircraftShapes, UI& ui, sf::Text& reset, sf::Text& settingstext, sf::RectangleShape& Settings, sf::RectangleShape& exitButton);

	sf::Vector2f mousePos;
private:
};