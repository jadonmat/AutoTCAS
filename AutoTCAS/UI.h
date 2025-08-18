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

    sf::Font getedgesFont() const;

    sf::Font getpixellariFont() const;

	sf::Text& getSettingsText(); // needed for events

	sf::RectangleShape& getSettings(); // needed for events

	sf::RectangleShape& getExitButton(); // needed for events

    sf::Text& getResetButton(); // needed for events



    void GenerateIntro(sf::RenderWindow& window, UI& ui, sf::Time dt);

	void GenerateFPS(sf::RenderWindow& window, UI& ui, sf::Time dt);

	void GenerateSettingsMenu(sf::RenderWindow& window, UI& ui);

    void DrawUI(sf::RenderWindow& window, sf::Time dt, UI& ui);

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Public member variables (need to be accessed in main) (may want to make these private later and make getters)

    //Fonts
	sf::Font edges; // needed in events
    sf::Font pixellari;


    bool showClickMessage;
    bool settingsMenuOpen;
	sf::Text settingsText{ edges }; // needed in events
	sf::RectangleShape settings; // needed in events
	sf::RectangleShape exitButton; // needed in events


    sf::Text reset{ edges }; // Needed in events

    // needed in events (move to events?)
    std::vector<sf::Text> tooCloseTexts;
    std::vector<float> tooCloseTimers;
    std::vector<float> tooCloseDurations;
    std::vector<sf::Vector2f> tooClosePositions;

    float scrollOffset;
    float maxScrollOffset;
    float scrollSpeed;

    // Scale constants
    static constexpr float MIN_SCALE = 0.4f;
    static constexpr float MAX_SCALE = 1.5f;
	static constexpr float MAX_SCALE_FPS = 0.85f;
    ///////////////////////////////////////////////////////////////////////////////////

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

    std::string currentFPSString;
};
