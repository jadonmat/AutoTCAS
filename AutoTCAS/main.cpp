#include <iostream>
#include <algorithm>
#include <Windows.h>
#include <vector>
#include "A380.h"
//#include <SFML/Graphics.hpp>
using namespace std;
#undef max
#undef min

//Function prototypes
enum class TextType { Setting, FPS };
void TextUpdate(sf::Text& text, sf::RenderWindow& window, sf::Font font, TextType type);
    
    //int main() {
    int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) {
        srand(time(0));

        //WINDOW GENERATION
        // 
        // Display the list of all the video modes available for fullscreen
            std::vector<sf::VideoMode> modes = sf::VideoMode::getFullscreenModes();
        for (std::size_t i = 0; i < modes.size(); ++i)
        {
            sf::VideoMode mode = modes[i];
            std::cout << "Mode #" << i << ": "
                << mode.size.x << "x" << mode.size.y << " - "
                << mode.bitsPerPixel << " bpp" << std::endl;
        }
    
        sf::VideoMode CurrentDesktopMode = sf::VideoMode::getDesktopMode();
        cout << "Current Desktop Mode: "
                << CurrentDesktopMode.size.x << "x" << CurrentDesktopMode.size.y << " - "
		    << CurrentDesktopMode.bitsPerPixel << " bpp" << std::endl;
        sf::VideoMode ScreenSizeMode = sf::VideoMode(CurrentDesktopMode.size, CurrentDesktopMode.bitsPerPixel);
        sf::ContextSettings settings;

        settings.antiAliasingLevel = 8; // Try 2, 4, or 8 (higher = smoother, but more performance cost)
        //sf::RenderWindow window(ScreenSizeMode, "AutoTCAS", sf::State::Fullscreen);
        //sf::RenderWindow window(sf::VideoMode({ 1250,750 }), "AutoTCAS", sf::Style::Default);
        //sf::RenderWindow window(ScreenSizeMode, "AutoTCAS", sf::Style::Default);

        sf::RenderWindow window(sf::VideoMode({ 1250,750 }), "AutoTCAS", sf::Style::Default, sf::State::Windowed, settings);
        //sf::RenderWindow window(ScreenSizeMode, "AutoTCAS", sf::Style::Default, sf::State::Windowed, settings);
        //window.setPosition(sf::Vector2i(-8, 0));

        window.setFramerateLimit(60);

        //BUTTONS
        // 
        // Settings BUTTON
        
        // Reset BUTTON (
        float x = window.getSize().x;
        float y = window.getSize().y;
        //sf::Font font("Fonts/Minecraftia-Regular.ttf");
        sf::Font font("Fonts/Edges.ttf");
        //sf::Font font("Fonts/39335_UniversCondensed.ttf");
        //sf::Font font("Fonts/07723_Cgothicb0.ttf");
        sf::Font font2("Fonts/Pixellari.ttf");
        sf::Text reset(font);
        reset.setString("RESET");
        TextUpdate(reset, window, font, TextType::Setting);

        //FPS display
        sf::Text fpsText(font2);
        TextUpdate(fpsText, window, font, TextType::FPS); 
        float frameTime = 0.f;
        int frameCount = 0;

        // Intro display
	    sf::Font clickFont("Fonts/Edges.ttf");
		sf::Text clickText(clickFont);
        clickText.setCharacterSize(40); // Adjust size as needed
        // Animated text setup
        std::string fullClickMessage = "Click anywhere to begin";
        size_t visibleChars = 0;
        float charInterval = 0.1f; // seconds between each character
        float charTimer = 0.f;
		bool showClickMessage = true;
        // Dot animation variables
        float dotInterval = 0.5f; // seconds per dot update
        float dotTimer = 0.f;
        int dotCount = 0; // will range from 0 to 3

        void start(); // starts time
        sf::Clock clock;

        vector<Aircraft*> aircrafts; //initialize vector of aircrafts
		vector<std::vector<sf::ConvexShape>> aircraftShapes; // each aircraft has a vector of shapes (deals with multiple shapes for aircrafts)


        // MAIN LOOP (after user clicks to start)
        while (window.isOpen()) {



            // EVENT LOOPS
            while (const std::optional event = window.pollEvent()) {

                // CLOSE EVENT
                if (event->is<sf::Event::Closed>()) {
                    window.close();
                }

                //CLOSE IF ESC IS PRESSED EVENT
                else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
                {

                    if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
                        window.close();
                }

                // MOUSE CLICK EVENT
                else if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>())
                {
                    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Vector2i(mouseButtonPressed->position.x, mouseButtonPressed->position.y));

                    //CREATING NEW AIRCRAFT WHERE CLICKED
                    if (mouseButtonPressed->button == sf::Mouse::Button::Left)
                    {
                        window.clear(sf::Color::Black); // Clears transparent rectangle
                        //prevents aircraft from being placed on each other
                        bool occupied = false;
                        for (const auto& aircraft : aircrafts) {
                            if (std::hypot((aircraft->getPosition().x) - mousePos.x, aircraft->getPosition().y - mousePos.y) < 180) { // checks if the distance
                                occupied = true;
                                break;
                            }
                        }
                        if (!occupied) {
                            //std::cout << "the left button was pressed" << std::endl;
                            //std::cout << "mouse x: " << mouseButtonPressed->position.x << std::endl;
                            //std::cout << "mouse y: " << mouseButtonPressed->position.y << std::endl;

                            // FOR A380: (ONLY OPTION RN)
                            A380* newAircraft = new A380();
                            newAircraft->setPosition(static_cast<sf::Vector2f>(mouseButtonPressed->position));
                            newAircraft->setHeadingAngle(rand() % 360);
                            aircrafts.push_back(newAircraft); //push_back adds a new element to the end of the vector
                            aircraftShapes.push_back(newAircraft->createA380Shape(.175f)); // Default for 1440p
                            std::cout << "Aircraft created at: " << mouseButtonPressed->position.x << ", " << mouseButtonPressed->position.y << endl;

                            // Hide the message after first aircraft is created
                            if (showClickMessage) {
                                showClickMessage = false;
                            }
                        }

                    }
                    // RESET BUTTON
                    if (reset.getGlobalBounds().contains(mousePos)) {
                        //std::cout << "the left button was pressed" << std::endl;
                        aircrafts.clear();
                        aircraftShapes.clear();
                        std::cout << "Reset Button pressed" << endl;
                        std::cout << "All Aircraft Deleted" << endl;
                    }
                }

                // AUTO RESIZE EVENT
                else if (const auto* resized = event->getIf<sf::Event::Resized>())
                {
                    // update the view to the new size of the window
                    sf::FloatRect visibleArea({ 0.f, 0.f }, sf::Vector2f(resized->size));
                    window.setView(sf::View(visibleArea));


                    // Clamp all aircraft positions to new window boundaries
                    sf::Vector2f windowSize(resized->size.x, resized->size.y);
                    for (int i = 0; i < aircrafts.size(); ++i) {
                        sf::Vector2f pos = aircrafts[i]->getPosition();
                        // Clamp x and y to keep aircraft within bounds
                        pos.x = std::max(aircrafts[i]->getRange(), std::min(pos.x, windowSize.x - aircrafts[i]->getRange()));
                        pos.y = std::max(aircrafts[i]->getRange(), std::min(pos.y, windowSize.y - aircrafts[i]->getRange()));
                        aircrafts[i]->setPosition(pos);

                    }
                    // Update message position if window resized
                    clickText.setPosition(sf::Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f));
                }

            } // END EVENT LOOPS




        //MAIN LOOP CODE
            sf::Time dt = clock.restart();

            //FPS display
            frameTime += dt.asSeconds();
            frameCount++;
            if (frameTime >= 1.f) {
                float fps = frameCount / frameTime;
                fpsText.setString("FPS: " + std::to_string(static_cast<int>(fps)));
                frameTime = 0.f;
                frameCount = 0;
            }

            // Clear window each dt;
            window.clear(sf::Color::Black);

            //BUTTON SCALING IN CASE OF CHANGED USER RESOLUTION: (ALSO IMPLEMENT INTO MENU LATER)
            TextUpdate(reset, window, font, TextType::Setting);
            TextUpdate(fpsText, window, font, TextType::FPS);

            // For loop to iterate through aircrafts.
            for (int i = 0; i < aircrafts.size(); ++i) {
                aircrafts[i]->update(dt); // Updates the aircraft position

                /* //DEFAULT AIRCRAFT SCALING BASED ON USER RESOLUTION: (ALSO IMPLEMENT INTO MENU LATER)
                 //cout << "Should Match:" << endl;

                 //1440p case
                 if (CurrentDesktopMode.size.x == 2560 && CurrentDesktopMode.size.y == 1440) {
                     // After setting the scale
                     aircrafts[i]->setShapeScale(0.26f);
                     aircraftShapes[i] = aircrafts[i]->createAircraftShape(aircrafts[i]->getShapeScale());
                     //cout << "2560x1440" << endl;
                 }
                 // 3.5k case
                 else if (CurrentDesktopMode.size.x == 3456 && CurrentDesktopMode.size.y == 2160) {
                     // After setting the scale
                     aircrafts[i]->setShapeScale(0.45f);
                     aircraftShapes[i] = aircrafts[i]->createAircraftShape(aircrafts[i]->getShapeScale());
                     //cout << "3456x1440" << endl;
                 }
                 else {
                     cout << "ERROR: Scaling does not match up" << endl;
                     return 0;
                 }

                */


                // Boundary interactions (Now integrated with aileron class)
                sf::Vector2f pos = aircrafts[i]->getPosition();
                sf::Vector2f vel = aircrafts[i]->getVelocity();
                bool updated = false;
                if (pos.x > window.getSize().x) {
                    pos.x = window.getSize().x;
                    vel.x = -vel.x;
                    aircrafts[i]->setVelocity(vel);
                    updated = true;
                }
                else if (pos.x < 0) {
                    pos.x = 0;
                    vel.x = -vel.x;
                    aircrafts[i]->setVelocity(vel);
                    updated = true;
                }
                else if (pos.y < 0) {
                    pos.y = 0;
                    vel.y = -vel.y;
                    aircrafts[i]->setVelocity(vel);
                    updated = true;
                }
                else if (pos.y > window.getSize().y) {
                    pos.y = window.getSize().y;
                    vel.y = -vel.y;
                    aircrafts[i]->setVelocity(vel);
                    updated = true;
                }
                //ensures pos and vel are updated
                //aircrafts[i].setPosition(pos);
                //aircrafts[i].setVelocity(vel);

                if (updated) {
                    float speed = std::sqrt(vel.x * vel.x + vel.y * vel.y);
                    if (speed > 0.001f) { // Avoid updating heading for near-zero velocity
                        float angleRadians = std::atan2(vel.y, vel.x);
                        float angleDegrees = angleRadians * (180.0f / 3.14f);
                        aircrafts[i]->setHeadingAngle(angleDegrees);
                    }
                }


                //just in case out of bounds (deletion)
                else if (pos.x - aircrafts[i]->getRange() > window.getSize().x) {

                    aircrafts.erase(aircrafts.begin() + i);
                    aircraftShapes.erase(aircraftShapes.begin() + i);
                    cout << "Out of bounds Aircraft Deleted" << endl;
                }
                else if (pos.x + aircrafts[i]->getRange() < 0) {

                    aircrafts.erase(aircrafts.begin() + i);
                    aircraftShapes.erase(aircraftShapes.begin() + i);
                    cout << "Out of bounds Aircraft Deleted" << endl;
                }
                else if (pos.y - aircrafts[i]->getRange() > window.getSize().y) {

                    aircrafts.erase(aircrafts.begin() + i);
                    aircraftShapes.erase(aircraftShapes.begin() + i);
                    cout << "Out of bounds Aircraft Deleted" << endl;
                }
                else if (pos.y + aircrafts[i]->getRange() < 0) {

                    aircrafts.erase(aircrafts.begin() + i);
                    aircraftShapes.erase(aircraftShapes.begin() + i);
                    cout << "Out of bounds Aircraft Deleted" << endl;
                }

                bool collisionDetected = false;
                bool warningDetected = false;

                // code related to TCAS detection (relates Aircraft and TCAS class)
                for (int j = 0; j < aircrafts.size(); ++j) {
                    if (i != j && aircrafts[i]->DetectAircraft(aircrafts[j])) {
                        warningDetected = true;
                    }
                    if (i != j && aircrafts[i]->DetectCollision(aircrafts[j])) {
                        collisionDetected = true;
                    }
                    for (auto& shape : aircraftShapes[i]) {
                        if (collisionDetected) {
                            shape.setFillColor(sf::Color::Red);
                        }
                        else if (warningDetected) {
                            shape.setFillColor(sf::Color{ 255,150,0 });
                        }
                        else {
                            shape.setFillColor(sf::Color::Green);
                        }
                    }
                }

                for (auto& ac : aircrafts) {
                    ac->avoidCollision(aircrafts, dt);
                }

                // constant determination of positions and headings
                for (auto& shape : aircraftShapes[i]) {
                    shape.setPosition(aircrafts[i]->getPosition());
                    shape.setRotation(aircrafts[i]->getHeadingAngle() + sf::degrees(90));
                    window.draw(shape);
                }

            }

			// animate click message
            if (showClickMessage) {
                charTimer += dt.asSeconds();
                if (visibleChars < fullClickMessage.size() && charTimer >= charInterval) {
                    ++visibleChars;
                    charTimer = 0.f;
                }

                std::string displayText = fullClickMessage.substr(0, visibleChars);

                if (visibleChars < fullClickMessage.size()) {
                    // always show an underscore at the end.
                    displayText += "_";
                }
                else {
                    // Full text is displayed; now animate a looping dot
                    dotTimer += dt.asSeconds();
                    if (dotTimer >= dotInterval) {
                        dotCount = (dotCount + 1) % 4; // cycle from 0 to 3
                        dotTimer = 0.f;
                    }
                    std::string dots(dotCount, '.');
                    displayText += dots;
                }

                clickText.setString(displayText);
                // Always set origin from the local bounds to keep it centered.
                clickText.setOrigin(clickText.getLocalBounds().position + clickText.getLocalBounds().size / 2.0f);
                clickText.setPosition(sf::Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f));

                // Optional: draw a semi-transparent overlay.
                sf::RectangleShape overlay(sf::Vector2f(window.getSize().x, window.getSize().y));
                overlay.setFillColor(sf::Color(0, 0, 0, 128));
                window.draw(overlay);
                window.draw(clickText);
            }

            if (!showClickMessage) {
                window.draw(reset);
                window.draw(fpsText);
            }

            window.display();

            // END MAIN LOOP CODE
        } 
        // END MAIN
        return 0;
    }
    
//Function Definitions


void TextUpdate(sf::Text& text, sf::RenderWindow& window, sf::Font font, TextType type) {
    unsigned int CharacterSize = 0;
	unsigned int CharacterSizeFPS = 0;
    sf::VideoMode CurrentDesktopMode = sf::VideoMode::getDesktopMode();
	//720p case
    if (CurrentDesktopMode.size.x == 1280 && CurrentDesktopMode.size.y == 720) {
        CharacterSize = 20.0f;
        CharacterSizeFPS = 10.0f;
        //cout << "1280x720" << endl;
    }
    //1080p case
    else if (CurrentDesktopMode.size.x == 1920 && CurrentDesktopMode.size.y == 1080) {
        CharacterSize = 25.f;
		CharacterSizeFPS = 12.5f;
        //cout << "1920x1080" << endl;
	}
    //1440p case
    else if (CurrentDesktopMode.size.x == 2560 && CurrentDesktopMode.size.y == 1440) {
        CharacterSize = 30.0f;
		CharacterSizeFPS = 15.0f;
        //cout << "2560x1440" << endl;
    }
    // 3.5k to 4k case
    else if (CurrentDesktopMode.size.x >= 3456 && CurrentDesktopMode.size.x <= 3840 && CurrentDesktopMode.size.y == 2160) {
        CharacterSize = 45.0f;
		CharacterSizeFPS = 22.5f;
        //cout << "3456x1440" << endl;
       
    }
    // 4k
    else {
        cout << "ERROR: Scaling does not match up" << endl;
        float textamt = 11;
        vector<sf::Text> ErrorTexts(textamt, sf::Text(font));
        
        sf::Clock errorClock;
        float errorTime = 30.f; // seconds

        // loop is taking over main loop until errorTime is reached
        while (errorClock.getElapsedTime().asSeconds() < errorTime) {
                // SFML 3.0 event loop
                while (const std::optional event = window.pollEvent()) {
                    if (event->is<sf::Event::Closed>()) {
                        window.close();
                        exit(1);
                    }
                    else if (const auto* resized = event->getIf<sf::Event::Resized>())
                    {
                        // update the view to the new size of the window
                        sf::FloatRect visibleArea({ 0.f, 0.f }, sf::Vector2f(resized->size));
                        window.setView(sf::View(visibleArea));
                    }
                }
            for (int i = 0; i < textamt; ++i) {
                ErrorTexts[i].setFont(font);
                ErrorTexts[i].setCharacterSize(25);
                ErrorTexts[i].setFillColor(sf::Color::Red);
                ErrorTexts[i].setOrigin(ErrorTexts[i].getLocalBounds().position + ErrorTexts[i].getLocalBounds().size / 2.0f);
                ErrorTexts[i].setPosition(sf::Vector2f(window.getSize().x / 2.f, window.getSize().y / 3.f + (i - 1) * 40.0f));
            }
            float secondsLeft = errorTime - errorClock.getElapsedTime().asSeconds();
                ErrorTexts[0].setString("ERROR: Incompatable Desktop Resolution.");
                ErrorTexts[1].setString(" ");
                ErrorTexts[2].setString("Current Resolution: " + std::to_string(CurrentDesktopMode.size.x) + "x" + std::to_string(CurrentDesktopMode.size.y));
                ErrorTexts[3].setString(" ");
                ErrorTexts[4].setString("Supported Desktop Resolutions (Set in Device Settings):");
                ErrorTexts[5].setString("3456x2160 up to 4k (3840x2160),");
                ErrorTexts[6].setString("2560x1440,"); 
                ErrorTexts[7].setString("1920x1080,");
                ErrorTexts[8].setString("1280x720");
				ErrorTexts[9].setString(" ");
                ErrorTexts[10].setString("Window will close in " + std::to_string(static_cast<int>(std::ceil(secondsLeft))) + " seconds.");
                
                window.clear(sf::Color::Black);
                for (int i = 0; i < textamt; ++i) {
                    ErrorTexts[i].setOrigin(ErrorTexts[i].getLocalBounds().position + ErrorTexts[i].getLocalBounds().size / 2.0f);
                    window.draw(ErrorTexts[i]);
                }
                    window.display();
        }
        window.close();
        exit(1);
    }
    float resetdiff = 10.f;
    if (type == TextType::Setting) {
        text.setFillColor(sf::Color::White);
        text.setCharacterSize(CharacterSize);
        sf::FloatRect bounds = text.getLocalBounds();
        sf::Vector2f center = bounds.getCenter();
        text.setPosition(sf::Vector2f(window.getSize().x - center.x * 2 - resetdiff, 5.f));
    }
    else if (type == TextType::FPS) {
        text.setFillColor(sf::Color::Green);
        text.setCharacterSize(CharacterSizeFPS);
        text.setPosition(sf::Vector2f(10.f, 5.f));
	}

}
