#include <iostream>
#include <algorithm>
#include <Windows.h>
#include <vector>
//Ends of Aircraft inheritance
#include "A380.h"
//Ends of Handling Inheritance
#include "UI.h"
#include "Events.h"
#include "Boundary.h"
#include "Window.h"
using namespace std;
#undef max
#undef min
    
    //int main() {
    int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) {
        srand(static_cast<unsigned int>(time(0)));

        //WINDOW GENERATION (my window class, not sfml)
		Window window;
		window.WindowGeneration(0); // default state (0 for windowed, 1 for fullscreen)

        //INITIALIZE BUTTONS (USING UI CLASS)
        UI ui;

        void start(); // starts time
        sf::Clock clock;

        vector<Aircraft*> aircrafts; //initialize vector of aircrafts
		vector<std::vector<sf::ConvexShape>> aircraftShapes; // each aircraft has a vector of shapes (deals with multiple shapes for aircrafts)


        // MAIN LOOP (after user clicks to start)
        while (window.window.isOpen()) {

        sf::Time dt = clock.restart();

        // Clear window each dt;
        window.window.clear(sf::Color::Black);

        Events Events;
		// Handle events in event class
		Events.handleEvents(window.window, aircrafts, aircraftShapes, ui, ui.reset, ui.settingsText, ui.settings, ui.exitButton, window);


        // Only update simulation if settings menu is not open (PAUSE FUNCTIONALITY)
        if (!ui.settingsMenuOpen) {
            // For loop to iterate through aircrafts (keep like this for now, in main)
            for (size_t i = 0; i < aircrafts.size(); ++i) {
                aircrafts[i]->update(dt); // Updates the aircraft position

                //// Boundary interactions (Boundary Class)
                Boundary boundary;
                boundary.BoundaryInteraction(static_cast<int>(i), window.window, aircrafts, aircraftShapes);


                // Avoid collision, change color, and draw aircrafts (Aircraft Class)
                float smoothingFactor = 0.05f; // Smoothing factor for position updates
                float maxTurnrate = 0.135f; // Maximum turn rate in degrees per second
                for (auto& ac : aircrafts) {
                    ac->DetectCollisionAndDraw(static_cast<int>(i), window.window, aircrafts, aircraftShapes, dt, smoothingFactor, maxTurnrate);
                }
            }
        }
        else {
            // Settings menu is open - simulation is paused
            // Still draw aircraft in their current positions but don't update them
            for (size_t i = 0; i < aircrafts.size(); ++i) {
				// Only draw the aircraft shapes without updating positions like in DetectCollisionAndDraw
                for (auto& shape : aircraftShapes[i]) {
                    window.window.draw(shape);
                }
            }
        }
	        
		ui.DrawUI(window.window, dt, ui, window); // Draws and animates UI elements

		window.window.display(); //Displays all the drawn shapes and text

        } 
        // END MAIN
        return 0;
    }
