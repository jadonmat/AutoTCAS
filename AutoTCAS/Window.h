#pragma once
#include <SFML/Graphics.hpp>

class Window {
public:
	Window();

	void WindowGeneration(int FrameRate, int antialiasing, int state);


	// public member variables (needs to be accessed in main)
	bool isFullscreen = false;
	sf::RenderWindow window;
};