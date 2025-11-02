#include "Events.h"
#include <iostream>
using namespace std;

Events::Events() {}

void Events::handleEvents(sf::RenderWindow& window, std::vector<Aircraft*>& aircrafts,
    std::vector<std::vector<sf::ConvexShape>>& aircraftShapes, UI& ui, sf::CircleShape& resetIconCircle, sf::CircleShape& settingsIconCircle, sf::RectangleShape& settingsIconTooth, sf::RectangleShape& settings, sf::RectangleShape& exitButton, Window& windowObj) {

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
                // Check if click is on UI buttons (settings or reset)
                // Only check settings bounds if menu is actually open
                bool clickedOnUI = false;
                if (resetIconCircle.getGlobalBounds().contains(mousePos) || settingsIconCircle.getGlobalBounds().contains(mousePos)) {
                    clickedOnUI = true;
                }
                // Only check settings rectangle collision if the menu is open
                if (ui.settingsMenuOpen && settings.getGlobalBounds().contains(mousePos)) {
                    clickedOnUI = true;
                }

                // Check for window mode button clicks when settings menu is open
                if (ui.settingsMenuOpen) {
                    if (ui.getWindowedButton().getGlobalBounds().contains(mousePos)) {
                        if (windowObj.isFullscreen) {
                            windowObj.toggleFullscreen();
                        }
                        clickedOnUI = true;
                    }
                    else if (ui.getFullscreenButton().getGlobalBounds().contains(mousePos)) {
                        if (!windowObj.isFullscreen) {
                            windowObj.toggleFullscreen();
                        }
                        clickedOnUI = true;
                    }
                }

                // Only create aircraft if settings menu is NOT open
                if (!occupied && !clickedOnUI && !ui.settingsMenuOpen) {
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
                else if (occupied && !clickedOnUI && !ui.settingsMenuOpen) {
                    sf::Text newTooCloseText{ ui.edges };
                    ui.tooCloseTexts.push_back(newTooCloseText);
                    ui.tooCloseTimers.push_back(0.0f);
                    ui.tooCloseDurations.push_back(1.0f);
                    ui.tooClosePositions.push_back(mousePos);
                }

            }
            // RESET BUTTON
            if (resetIconCircle.getGlobalBounds().contains(mousePos) && !ui.settingsMenuOpen) {
                //std::cout << "the left button was pressed" << std::endl;
                aircrafts.clear();
                aircraftShapes.clear();
				ui.resetButtonPressed = true;
                std::cout << "Reset Button pressed" << endl;
                std::cout << "All Aircraft Deleted" << endl;
            }

            // SETTINGS BUTTON
            if (settingsIconCircle.getGlobalBounds().contains(mousePos) && settingsIconTooth.getGlobalBounds().contains(mousePos)) {
                if (!ui.settingsMenuOpen) {
                    ui.GenerateSettingsMenu(window, ui, windowObj);
                    ui.settingsMenuOpen = true;
                }
            }

            //settings close behavior
            if (ui.settingsMenuOpen) {
                if (exitButton.getGlobalBounds().contains(mousePos)) {
                    ui.settingsMenuOpen = false;
                }
            }


        }

        // AUTO RESIZE EVENT
        else if (const auto* resized = event->getIf<sf::Event::Resized>())
        {
            // Enforce minimum window size
            sf::Vector2u newSize = resized->size;
            bool needsResize = false;
            
            if (newSize.x < Window::MIN_WIDTH) {
                newSize.x = Window::MIN_WIDTH;
                needsResize = true;
            }
            if (newSize.y < Window::MIN_HEIGHT) {
                newSize.y = Window::MIN_HEIGHT;
                needsResize = true;
            }
            
            if (needsResize) {
                window.setSize(newSize);
            }

            // update the view to the new size of the window
            sf::FloatRect visibleArea({ 0.0f, 0.0f }, sf::Vector2f(static_cast<float>(newSize.x), static_cast<float>(newSize.y)));
            window.setView(sf::View(visibleArea));


            // Clamp all aircraft positions to new window boundaries
            sf::Vector2f windowSize(static_cast<float>(newSize.x), static_cast<float>(newSize.y));
            for (size_t i = 0; i < aircrafts.size(); ++i) {
                sf::Vector2f pos = aircrafts[i]->getPosition();
                // Clamp x and y to keep aircraft within bounds
                pos.x = std::max(aircrafts[i]->getRange(), std::min(pos.x, windowSize.x - aircrafts[i]->getRange()));
                pos.y = std::max(aircrafts[i]->getRange(), std::min(pos.y, windowSize.y - aircrafts[i]->getRange()));
                aircrafts[i]->setPosition(pos);

            }
            // Update message position if window resized
            sf::Vector2f center = ui.settings.getGeometricCenter();
            settings.setPosition(sf::Vector2f(static_cast<float>(window.getSize().x) / 2.0f - center.x, static_cast<float>(window.getSize().y) / 2.0f - center.y));
        }

        // scroll wheel support
        else if (const auto* mouseWheelScrolled = event->getIf<sf::Event::MouseWheelScrolled>())
        {
            if (ui.settingsMenuOpen && ui.getSettings().getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                ui.scrollOffset -= mouseWheelScrolled->delta * ui.scrollSpeed;
            }
        }

    } // END EVENT LOOPS

}