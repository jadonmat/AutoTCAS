#include "Events.h"
#include <iostream>
using namespace std;

Events::Events() {}

void Events::handleEvents(sf::RenderWindow& window, std::vector<Aircraft*>& aircrafts, 
	std::vector<std::vector<sf::ConvexShape>>& aircraftShapes, UI& ui, sf::Text& clickText, sf::Text& fpsText, sf::Text& reset) {

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
                    if (std::hypot((aircraft->getPosition().x) - mousePos.x, aircraft->getPosition().y - mousePos.y) < 180.0f) { // checks if the distance
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
                    newAircraft->setPosition(sf::Vector2f(static_cast<float>(mouseButtonPressed->position.x), static_cast<float>(mouseButtonPressed->position.y)));
                    newAircraft->setHeadingAngle(static_cast<float>(rand() % 360));
                    aircrafts.push_back(newAircraft); //push_back adds a new element to the end of the vector
                    aircraftShapes.push_back(newAircraft->createAircraftShape(0.175f)); // Default for 1440p
                    std::cout << "Aircraft created at: " << mouseButtonPressed->position.x << ", " << mouseButtonPressed->position.y << endl;

                
                    // Hide the message after first aircraft is created
                    if (ui.showClickMessage) {
                        ui.showClickMessage = false;
                    }
                }
                else if (occupied) {
                    sf::Text newTooCloseText{ ui.edges };
                    ui.tooCloseTexts.push_back(newTooCloseText);
                    ui.tooCloseTimers.push_back(0.0f);
                    ui.tooCloseDurations.push_back(1.5f);
                    ui.tooClosePositions.push_back(mousePos);
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
            sf::FloatRect visibleArea({ 0.0f, 0.0f }, sf::Vector2f(static_cast<float>(resized->size.x), static_cast<float>(resized->size.y)));
            window.setView(sf::View(visibleArea));


            // Clamp all aircraft positions to new window boundaries
            sf::Vector2f windowSize(static_cast<float>(resized->size.x), static_cast<float>(resized->size.y));
            for (size_t i = 0; i < aircrafts.size(); ++i) {
                sf::Vector2f pos = aircrafts[i]->getPosition();
                // Clamp x and y to keep aircraft within bounds
                pos.x = std::max(aircrafts[i]->getRange(), std::min(pos.x, windowSize.x - aircrafts[i]->getRange()));
                pos.y = std::max(aircrafts[i]->getRange(), std::min(pos.y, windowSize.y - aircrafts[i]->getRange()));
                aircrafts[i]->setPosition(pos);

            }
            // Update message position if window resized
            clickText.setPosition(sf::Vector2f(static_cast<float>(window.getSize().x) / 2.0f, static_cast<float>(window.getSize().y) / 2.0f));
        }

    } // END EVENT LOOPS

}