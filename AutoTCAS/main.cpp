#include <iostream>
#include <vector>
#include "Aircraft.h"
//#include <SFML/Graphics.hpp>

using namespace std;

int main() {
    srand(time(0));

    // Display the list of all the video modes available for fullscreen
    /* std::vector<sf::VideoMode> modes = sf::VideoMode::getFullscreenModes();
    for (std::size_t i = 0; i < modes.size(); ++i)
    {
        sf::VideoMode mode = modes[i];
        std::cout << "Mode #" << i << ": "
            << mode.size.x << "x" << mode.size.y << " - "
            << mode.bitsPerPixel << " bpp" << std::endl;
    }
    */
    sf::VideoMode CurrentDesktopMode = sf::VideoMode::getDesktopMode();
    sf::VideoMode ScreenSizeMode = sf::VideoMode(CurrentDesktopMode.size);
    sf::ContextSettings settings;
    settings.antiAliasingLevel = 8; // Try 2, 4, or 8 (higher = smoother, but more performance cost)
    //sf::RenderWindow window(FullScreenMode, "AutoTCAS", sf::State::Fullscreen);
    //sf::RenderWindow window(sf::VideoMode({ 1250,750 }), "AutoTCAS", sf::Style::Default);
    //sf::RenderWindow window(ScreenSizeMode, "AutoTCAS", sf::Style::Default);
    sf::RenderWindow window(sf::VideoMode({ 1024, 768 }, CurrentDesktopMode.bitsPerPixel), "AutoTCAS", sf::Style::Default, sf::State::Windowed, settings);

    window.setFramerateLimit(60);


    // RESET BUTTON
    float x = window.getSize().x;
    float y = window.getSize().y;
    sf::Font font("Fonts/Minecraftia-Regular.ttf");
    sf::Text reset(font);
    reset.setString("RESET");
    reset.setCharacterSize(15);
    reset.setFillColor(sf::Color::White);
    float diffx = 65;
    float diffy = 15;
    reset.setPosition(sf::Vector2f(x-diffx,diffy));

    //FPS display
    sf::Text fpsText(font);
    fpsText.setCharacterSize(11);
    fpsText.setFillColor(sf::Color::White);
    fpsText.setPosition(sf::Vector2f(10, 10));
    float frameTime = 0.f;
    int frameCount = 0;


    void start(); // starts time
    sf::Clock clock;

    vector<Aircraft> aircrafts; //initialize vector of aircrafts
    vector<sf::ConvexShape> aircraftShapes; //corresponding vector of aircraft shapes

    // MAIN LOOP
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

            // AUTO RESIZE EVENT
            else if (const auto* resized = event->getIf<sf::Event::Resized>())
            {
                // update the view to the new size of the window
                sf::FloatRect visibleArea({ 0.f, 0.f }, sf::Vector2f(resized->size));
                window.setView(sf::View(visibleArea));

                
                // Clamp all aircraft positions to new window boundaries
                sf::Vector2f windowSize(resized->size.x, resized->size.y);
                for (int i = 0; i < aircrafts.size(); ++i) {
                    sf::Vector2f pos = aircrafts[i].getPosition();
                    // Clamp x and y to keep aircraft within bounds
                    pos.x = std::max(aircrafts[i].getRange(), std::min(pos.x, windowSize.x - aircrafts[i].getRange()));
                    pos.y = std::max(aircrafts[i].getRange(), std::min(pos.y, windowSize.y - aircrafts[i].getRange()));
                    aircrafts[i].setPosition(pos);

                }
                //CLAMP reset button to new window, bc on right side (unlike fps)
                reset.setPosition(sf::Vector2f(windowSize.x - diffx, diffy));
                //reset.setPosition(reset.getPosition() + sf::Vector2f(6, diffy));
            }

            // MOUSE CLICK EVENT
            else if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>())
            {
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Vector2i(mouseButtonPressed->position.x, mouseButtonPressed->position.y));

                //CREATING NEW AIRCRAFT WHERE CLICKED
                if (mouseButtonPressed->button == sf::Mouse::Button::Left)
                {
                    //prevents aircraft from being placed on each other
                    bool occupied = false;
                    for (const auto& aircraft : aircrafts) {
                        if (std::hypot((aircraft.getPosition().x) - mousePos.x, aircraft.getPosition().y - mousePos.y) < 135) { // checks if the distance
                            occupied = true;
                            break;
                        }
                    }
                    if (!occupied) {
                        //std::cout << "the left button was pressed" << std::endl;
                        //std::cout << "mouse x: " << mouseButtonPressed->position.x << std::endl;
                        //std::cout << "mouse y: " << mouseButtonPressed->position.y << std::endl;

                        Aircraft newAircraft;
                        newAircraft.setPosition(static_cast<sf::Vector2f>(mouseButtonPressed->position));
                        newAircraft.setHeadingAngle(rand() % 360);
                        aircrafts.push_back(newAircraft); //push_back adds a new element to the end of the vector
                        aircraftShapes.push_back(newAircraft.createAircraftShape());
                        std::cout << "Aircraft created at: " << mouseButtonPressed->position.x << ", " << mouseButtonPressed->position.y << endl;
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
        
        // For loop to iterate through aircrafts.
        for (int i = 0; i < aircrafts.size(); ++i) {
            aircrafts[i].update(dt); // Updates the aircraft position

            // Boundary interactions (Now integrated with aileron class)
            sf::Vector2f pos = aircrafts[i].getPosition();
            sf::Vector2f vel = aircrafts[i].getVelocity();
            bool updated = false;
            if (pos.x > window.getSize().x) {
                pos.x = window.getSize().x;
                vel.x = -vel.x;
                aircrafts[i].setVelocity(vel);
                updated = true;
            }
            else if (pos.x < 0) {
                pos.x = 0;
                vel.x = -vel.x;
                aircrafts[i].setVelocity(vel);
                updated = true;
            }
            else if (pos.y < 0) {
                pos.y = 0;
                vel.y = -vel.y;
                aircrafts[i].setVelocity(vel);
                updated = true;
            }
            else if (pos.y > window.getSize().y) {
                pos.y = window.getSize().y;
                vel.y = -vel.y;
                aircrafts[i].setVelocity(vel);
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
                    aircrafts[i].setHeadingAngle(angleDegrees);
                }
            }


            //just in case out of bounds (deletion)
            else if (pos.x - aircrafts[i].getRange() > window.getSize().x) {

                aircrafts.erase(aircrafts.begin() + i);
                aircraftShapes.erase(aircraftShapes.begin() + i);
                cout << "Out of bounds Aircraft Deleted" << endl;
            }
            else if (pos.x + aircrafts[i].getRange() < 0) {

                aircrafts.erase(aircrafts.begin() + i);
                aircraftShapes.erase(aircraftShapes.begin() + i);
                cout << "Out of bounds Aircraft Deleted" << endl;
            }
            else if (pos.y - aircrafts[i].getRange() > window.getSize().y) {

                aircrafts.erase(aircrafts.begin() + i);
                aircraftShapes.erase(aircraftShapes.begin() + i);
                cout << "Out of bounds Aircraft Deleted" << endl;
            }
            else if (pos.y + aircrafts[i].getRange() < 0) {

                aircrafts.erase(aircrafts.begin() + i);
                aircraftShapes.erase(aircraftShapes.begin() + i);
                cout << "Out of bounds Aircraft Deleted" << endl;
            }
            
            bool collisionDetected = false;
            bool warningDetected = false;

            // code related to TCAS detection (relates Aircraft and TCAS class)
            for (int j = 0; j < aircrafts.size(); ++j) {
                if (i != j && aircrafts[i].DetectAircraft(aircrafts[j])) {
                    warningDetected = true;
                }   
                if (i != j && aircrafts[i].DetectCollision(aircrafts[j])) {
                    collisionDetected = true;
                }
                if (collisionDetected) {
                    aircraftShapes[i].setFillColor(sf::Color::Red);
                }
                else if (warningDetected) {
                    aircraftShapes[i].setFillColor(sf::Color{255,150,0});
                }
                else {
                    aircraftShapes[i].setFillColor(sf::Color::Green);
                }
            }

            for (auto& ac : aircrafts) {
                ac.avoidCollision(aircrafts, dt);
            }

            // constant determination of positions and headings
            aircraftShapes[i].setPosition(aircrafts[i].getPosition());
            aircraftShapes[i].setRotation(aircrafts[i].getHeadingAngle() + sf::degrees(90));
            window.draw(aircraftShapes[i]);

        }

        //window.draw(resetButton);
        window.draw(reset);
        // Draw FPS text
        window.draw(fpsText);
        window.display();

        // END MAIN LOOP CODE
    } 
    // END MAIN
    return 0;
}