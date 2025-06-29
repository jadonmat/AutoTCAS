#include <iostream>
#include <vector>
#include "Aircraft.h"
//#include "TCAS.h"
//#include "Aileron.h"
//#include "Engine.h"
//#include <SFML/Graphics.hpp>

using namespace std;

int main() {
    srand(time(0));

    sf::VideoMode CurrentDesktopMode = sf::VideoMode::getDesktopMode();
    sf::VideoMode FullScreenMode = sf::VideoMode(CurrentDesktopMode.size);

    //sf::RenderWindow window(FullScreenMode, "AutoTCAS", sf::State::Fullscreen);
    sf::RenderWindow window(sf::VideoMode({ 1250,750 }), "AutoTCAS", sf::Style::Default); // Pass settings object
    void start(); // starts time
    sf::Clock clock;

    vector<Aircraft> aircrafts; //initialize vector of aircrafts
    vector<sf::ConvexShape> aircraftShapes; //corresponding vector of aircraft shapes

    // RESET BUTTON
    float x = window.getSize().x;
    float y = window.getSize().y;
    sf::RectangleShape resetButton;

    resetButton.setPosition(sf::Vector2f(x - 85, 0 + 10));
    resetButton.setSize(sf::Vector2f(75, 30));
    resetButton.setFillColor(sf::Color::White);
    resetButton.setOutlineColor(sf::Color::White);
    resetButton.setOutlineThickness(2.0f);

    // Set up the button's text
    sf::Font font("Fonts/Minecraftia-Regular.ttf");
    sf::Text text(font);
    text.setString("RESET");
    text.setCharacterSize(17);
    text.setFillColor(sf::Color::Black);

    // Center the text within the rectangle
    text.setPosition(resetButton.getPosition() + sf::Vector2f(6, 15));

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
                //CLAMP reset button to new window
                sf::Vector2f first(85, 0);
                resetButton.setPosition(sf::Vector2f(windowSize.x - first.x, 0 + 10));
                text.setPosition(resetButton.getPosition() + sf::Vector2f(6, 15));
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
                        if (std::hypot((aircraft.getPosition().x) - mousePos.x, aircraft.getPosition().y - mousePos.y) < 50) { // checks if the distance
                            occupied = true;
                            break;
                        }
                    }
                    if (!occupied) {
                        std::cout << "the left button was pressed" << std::endl;
                        std::cout << "mouse x: " << mouseButtonPressed->position.x << std::endl;
                        std::cout << "mouse y: " << mouseButtonPressed->position.y << std::endl;

                        Aircraft newAircraft;
                        newAircraft.setPosition(static_cast<sf::Vector2f>(mouseButtonPressed->position));
                        newAircraft.setHeadingAngle(rand() % 360);
                        aircrafts.push_back(newAircraft); //push_back adds a new element to the end of the vector
                        aircraftShapes.push_back(newAircraft.createAircraftShape());
                        cout << "Aircraft created at: " << mouseButtonPressed->position.x << ", " << mouseButtonPressed->position.y << endl;
                    }

                }
                // RESET BUTTON
                if (resetButton.getGlobalBounds().contains(mousePos)) {
                    std::cout << "the left button was pressed" << std::endl;
                    aircrafts.clear();
                    aircraftShapes.clear();
                    cout << "Reset Button pressed" << endl;
                    cout << "All Aircraft Deleted" << endl;
                }
            }
        }

        //MAIN LOOP CODE

        sf::Time dt = clock.restart();
        window.clear();



        for (int i = 0; i < aircrafts.size(); ++i) {
            aircrafts[i].update(dt);
            bool collisionDetected = false;
            // Boundary interactions
            sf::Vector2f pos = aircrafts[i].getPosition();
            sf::Vector2f vel = aircrafts[i].getVelocity();
            if (pos.x > window.getSize().x) {
                vel.x = -vel.x;
                aircrafts[i].setVelocity(vel);
            }
            else if (pos.x < 0) {
                vel.x = -vel.x;
                aircrafts[i].setVelocity(vel);

            }
            else if (pos.y < 0) {
                vel.y = -vel.y;
                aircrafts[i].setVelocity(vel);

            }
            else if (pos.y > window.getSize().y) {
                vel.y = -vel.y;
                aircrafts[i].setVelocity(vel);
            }
            //just in case out of bounds
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


            for (int j = 0; j < aircrafts.size(); ++j) {
                if (i != j && aircrafts[i].detectAircraft(aircrafts[j])) {
                    aircraftShapes[i].setFillColor(sf::Color::Red);
                    aircraftShapes[j].setFillColor(sf::Color::Red);
                    collisionDetected = true;

                }
            }
            if (!collisionDetected) {
                aircraftShapes[i].setFillColor(sf::Color::Green);
            }
            aircraftShapes[i].setPosition(aircrafts[i].getPosition());
            aircraftShapes[i].setRotation(aircrafts[i].getHeadingAngle() + sf::degrees(90));
            window.draw(aircraftShapes[i]);


            for (auto& ac : aircrafts) {
                ac.avoidCollision(aircrafts, dt);
            }
        }

        window.draw(resetButton);
        window.draw(text);
        window.display();
    }

    return 0;
}