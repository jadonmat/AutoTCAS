#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "A380.h"
class Window; // Forward declaration
using namespace std;

class UI {
public:
    // Class constructor
    UI();
    //Class member functions

    sf::Font getedgesFont() const;

    sf::Font getpixellariFont() const;

    sf::Font getarialFont() const;

	sf::CircleShape& getSettingsIconCircle(); // needed for events

	sf::RectangleShape& getSettingsIconTooth(); // needed for events

	sf::RectangleShape& getSettings(); // needed for events

	sf::RectangleShape& getExitButton(); // needed for events

    sf::CircleShape& getResetIconCircle(); // needed for events

	sf::ConvexShape& getResetIconArrow(); // needed for events

	sf::RectangleShape& getResetIconRectangle(); // needed for events

    // Window mode button getters
    sf::RectangleShape& getWindowedButton();
    sf::RectangleShape& getFullscreenButton();

    void GenerateIntro(sf::RenderWindow& window, UI& ui, sf::Time dt);

	void GenerateFPS(sf::RenderWindow& window, UI& ui, sf::Time dt);

	void GenerateSettingsMenu(sf::RenderWindow& window, UI& ui, const Window& windowObj);

    void DrawUI(sf::RenderWindow& window, sf::Time dt, UI& ui, const Window& windowObj);

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Public member variables (need to be accessed in main) (may want to make these private later and make getters)

    //Fonts
	sf::Font edges; // needed in events
    sf::Font pixellari;
	sf::Font arial;


	bool showClickMessage; // needed in events
	bool settingsMenuOpen; // needed in events
	bool resetButtonPressed;// needed in events

    sf::CircleShape settingsIconCircle; //needed in events
    sf::RectangleShape settingsIconTooth; // needed in events
	sf::RectangleShape settings; // needed in events
	sf::RectangleShape exitButton; // needed in events
	sf::CircleShape resetIconCircle; // needed in events
	sf::ConvexShape resetIconArrow; // needed in events
    sf::RectangleShape resetIconRectangle; // needed in events

    // Window mode buttons
    sf::RectangleShape windowedButton; // needed in events
    sf::RectangleShape fullscreenButton; // needed in events

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
    static constexpr float MAX_SCALE = .7f;
	static constexpr float MAX_SCALE_FPS = 0.85f;
	static constexpr float MAX_SCALE_SETTINGS = 0.5f; // For settings menu scaling
    static constexpr float MIN_SETTINGS_WIDTH = 400.0f;  // Minimum settings menu width
    static constexpr float MAX_SETTINGS_WIDTH = 1300.0f;
    static constexpr float MAX_SETTINGS_HEIGHT = 1000.0f;
    ///////////////////////////////////////////////////////////////////////////////////

private:
    //Private member variables
   
	//Reset Text variables
    float resetTextTimer;
    float resetTextDuration;
    bool showResetText;

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

    std::unique_ptr<A380> introAircraft;
    std::vector<sf::ConvexShape> introAircraftShapes;
};
