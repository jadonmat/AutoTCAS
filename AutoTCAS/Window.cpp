#include "Window.h"
#include <iostream>
using namespace std;

Window::Window() {}

void Window::WindowGeneration(int framerate, int antialiasing, int state) {
    // Display the list of all the video modes available for fullscreen
    std::vector<sf::VideoMode> modes = sf::VideoMode::getFullscreenModes();
    for (std::size_t i = 0; i < modes.size(); ++i)
    {
        sf::VideoMode mode = modes[i];
        //std::cout << "Mode #" << i << ": "
        //    << mode.size.x << "x" << mode.size.y << " - "
        //    << mode.bitsPerPixel << " bpp" << std::endl;
    }

    sf::VideoMode CurrentDesktopMode = sf::VideoMode::getDesktopMode();
    /*cout << "Current Desktop Mode: "
        << CurrentDesktopMode.size.x << "x" << CurrentDesktopMode.size.y << " - "
        << CurrentDesktopMode.bitsPerPixel << " bpp" << std::endl;*/
    sf::VideoMode ScreenSizeMode = sf::VideoMode(CurrentDesktopMode.size, CurrentDesktopMode.bitsPerPixel);
    sf::ContextSettings settings;

    settings.antiAliasingLevel = antialiasing; // Try 2, 4, or 8 (higher = smoother, but more performance cost)
    if (state == 0) {
    window.create(sf::VideoMode({ 1250,750 }), "AutoTCAS", sf::Style::Default, sf::State::Windowed, settings);
    }
    else if (state == 1) {
    window.create(sf::VideoMode({ 1250,750 }), "AutoTCAS", sf::Style::Default, sf::State::Fullscreen, settings);
    }

    window.setFramerateLimit(framerate);
}