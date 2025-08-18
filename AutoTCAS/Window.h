#pragma once
#include <SFML/Graphics.hpp>

class Window {
public:
	Window();

	void WindowGeneration(int FrameRate, int antialiasing, int state);
	void MinimumSize();

	// Add minimum size constants
	static constexpr unsigned int MIN_WIDTH = 800;
	static constexpr unsigned int MIN_HEIGHT = 500;

	// public member variables (needs to be accessed in main)
	bool isFullscreen = false;
	sf::RenderWindow window;
};