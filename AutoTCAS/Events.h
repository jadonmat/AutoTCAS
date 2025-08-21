#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Aircraft.h"
#include "A380.h"
#include "UI.h"
#include "Window.h"

class Events {
public:
	Events();

	void handleEvents(sf::RenderWindow& window, std::vector<Aircraft*>& aircrafts,
		std::vector<std::vector<sf::ConvexShape>>& aircraftShapes, UI& ui, sf::Text& reset, sf::Text& settingsText, sf::RectangleShape& settings, sf::RectangleShape& exitButton, Window& windowObj);

};