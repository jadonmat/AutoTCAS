#pragma once
#include <SFML/Graphics.hpp>

class Window {
public:
	Window();

	void WindowGeneration(int state);
	void MinimumSize();
	
	// Method to get current window mode as string
	std::string getCurrentWindowModeString() const;
	
	// Method to toggle between fullscreen and windowed mode
	void toggleFullscreen();

	// Add minimum size constants
	static constexpr unsigned int MIN_WIDTH = 800;
	static constexpr unsigned int MIN_HEIGHT = 500;

	// public member variables (needs to be accessed in main)
	bool isFullscreen = false;
	sf::RenderWindow window;

private:
	int framerate;
	int antialiasing;
};