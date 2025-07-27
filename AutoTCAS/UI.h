#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
//#include "Aircraft.h"
using namespace std;

class UI {
public:
    // Class constructor
    UI();
    //Class member functions
    //Fonts
    sf::Font getedgesFont() const;
    sf::Font getpixellariFont() const;

    //RESET
    sf::Text& getResetButton();

    //FPS
    sf::Text& getFPSDisplay();

    //Click text
    sf::Text& getClickText();

    //Too close message
    sf::Text& getTooCloseMessage();

    //Update UI scaling and generate text shapes based on user resolution  
    enum class TextType { Reset, FPS, Click, TooClose };
    void TextUpdate(sf::Text& text, sf::RenderWindow& window, TextType type);

    //Initialize UI elements
    void InitializeUI(sf::RenderWindow& window, UI& ui);

    // Draw and/or animate UI elements
    void DrawAndOrAnimate(sf::RenderWindow& window, sf::Time dt, UI& ui);

    //////////////////////////////////////////////////////////////
	//Public member variables (need to be accessed in main) (may want to make these private later and make getters)
    bool showClickMessage;
    sf::Font edges = getedgesFont();
    sf::Text reset{ edges };
    sf::Font pixellari = getpixellariFont();
    sf::Text fpsText{ pixellari };
    sf::Text clickText{ edges };
    sf::Text TooClose{ edges };
    // Vector-based too close messages (without structs)
    std::vector<sf::Text> tooCloseTexts;
    std::vector<float> tooCloseTimers;
    std::vector<float> tooCloseDurations;
    std::vector<sf::Vector2f> tooClosePositions;

private:
    //Private member variables

    //FPS display variables
    float frameTime;
    float frameCount;

    //Click text variables
    std::string fullClickMessage;
    size_t visibleChars;
    float charInterval;
    float charTimer;

    // Dot animation variables
    float dotInterval;
    float dotTimer;
    int dotCount;
};
