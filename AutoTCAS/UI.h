#pragma once
#include <SFML/Graphics.hpp>
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
    void FPSDisplay(sf::Time dt, sf::Text& fpsText);

    //Too close message
    sf::Text& getTooCloseMessage();
    void showTooCloseMessageFor(float duration = 2.0f); // Add this line

    //Click text
    sf::Text& getClickText();

    //Update UI scaling and generate text shapes based on user resolution  
    enum class TextType { Reset, FPS, Click, TooClose };
    void TextUpdate(sf::Text& text, sf::RenderWindow& window, TextType type) const;

    //Initialize UI elements
    void InitializeUI(sf::RenderWindow& window, UI& ui);

    // Draw and/or animate UI elements
    void DrawAndOrAnimate(sf::RenderWindow& window, sf::Time dt, UI& ui);

    //////////////////////////////////////////////////////////////
    //Public member variable (need to be accessed in main)
    bool showClickMessage;
    bool showTooCloseMessage;
    sf::Font edges = getedgesFont();
    sf::Text reset{ edges };
    sf::Font pixellari = getpixellariFont();
    sf::Text fpsText{ pixellari };
    sf::Text clickText{ edges };
    sf::Text TooClose{ edges };
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

    // Too Close message timing variables
    float tooCloseTimer;
    float tooCloseDisplayDuration;
};
