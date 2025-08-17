//Seperate class, not related to the aircraft inherentence structure.
#include <iostream>
#include <vector>
#include "UI.h"
using namespace std;

UI::UI() {
    //edges = getedgesFont();
    //sf::Text reset{ edges };
    frameTime = 0.0f;
    frameCount = 0.0f;
    visibleChars = 0;
    charInterval = 0.1f; // seconds between each character
    charTimer = 0.0f;
    showClickMessage = true;
    dotInterval = 0.5f; // seconds per dot update
    dotTimer = 0.0f;
    dotCount = 0; // will range from 0 to 3
    fullClickMessage = "Click anywhere to begin";
    settingsMenuOpen = false;
    scrollOffset = 0.0f;
    maxScrollOffset = 0.0f;
    scrollSpeed = 50.0f;

}


sf::Font UI::getedgesFont() const {
    sf::Font edgesFont("Fonts/Edges.ttf");
    return edgesFont;
}

sf::Font UI::getpixellariFont() const {
	sf::Font pixellariFont("Fonts/Pixellari.ttf");
	return pixellariFont;
}

sf::Text& UI::getSettingsText() {
    return settingsText;
}
sf::RectangleShape& UI::getSettings() {
    return settings; 
}
sf::Text& UI::getSettingsHeader() {
    return SettingsHeader; 
}
sf::RectangleShape& UI::getExitButton() {
    return exitButton; 
}
sf::Text& UI::getExitText() {
    return exitText; 
}
sf::Text& UI::getPauseText() {
    return pauseText; 
}
sf::Text& UI::getWindowSettingsText() {
    return WindowSettingsText; 
}
sf::Text& UI::getWindowModeText() {
    return WindowModeText; 
}
sf::Text& UI::getFullscreenText() {
    return FullscreenText; 
}
sf::Text& UI::getWindowedText() {
    return WindowedText; 
}

sf::Text& UI::getResetButton() {
    return reset; 
}

sf::Text& UI::getFPSDisplay() {
    return fpsText; 
}

sf::Text& UI::getClickText() {
    return clickText; 
}

sf::Text& UI::getNameText() {
    return nameText; 
}

sf::Text& UI::getTooCloseMessage() {
    return TooClose;
}


// handles differnet buttons with texttype
void UI::TextUpdate(sf::Text& text, sf::RenderWindow& window, TextType type) {
    sf::Font font = getedgesFont();
    float CharacterSize = 0.0f;
    float CharacterSizeFPS = 0.0f;
	float TooCloseCharacterSize = 0.0f;
    sf::VideoMode CurrentDesktopMode = sf::VideoMode::getDesktopMode();
    //720p case
    if (CurrentDesktopMode.size.x == 1280u && CurrentDesktopMode.size.y == 720u) {
        CharacterSize = 20.0f;
        CharacterSizeFPS = 10.0f;
        TooCloseCharacterSize = 8.0f;
        //cout << "1280x720" << endl;
    }
    //1080p case
    else if (CurrentDesktopMode.size.x == 1920u && CurrentDesktopMode.size.y == 1080u) {
        CharacterSize = 25.0f;
        CharacterSizeFPS = 12.5f;
		TooCloseCharacterSize = 8.0f;
        //cout << "1920x1080" << endl;
    }
    //1440p case
    else if (CurrentDesktopMode.size.x == 2560u && CurrentDesktopMode.size.y == 1440u) {
        CharacterSize = 30.0f;
        CharacterSizeFPS = 15.0f;
		TooCloseCharacterSize = 10.0f;
        //cout << "2560x1440" << endl;
    }
    // 3.5k to 4k case
    else if (CurrentDesktopMode.size.x >= 3456u && CurrentDesktopMode.size.x <= 3840u && CurrentDesktopMode.size.y == 2160u) {
        CharacterSize = 45.0f;
        CharacterSizeFPS = 27.5f;
        TooCloseCharacterSize = 11.0f;
        //cout << "3456x1440" << endl;
    }
    // 4k
    else {
        cout << "ERROR: Scaling does not match up" << endl;
        int textamt = 11;
        vector<sf::Text> ErrorTexts(static_cast<size_t>(textamt), sf::Text(font));

        sf::Clock errorClock;
        float errorTime = 45.0f; // seconds

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
                    sf::FloatRect visibleArea({ 0.0f, 0.0f }, sf::Vector2f(resized->size));
                    window.setView(sf::View(visibleArea));
                }
            }
            for (int i = 0; i < textamt; ++i) {
                ErrorTexts[static_cast<size_t>(i)].setFont(font);
                ErrorTexts[static_cast<size_t>(i)].setCharacterSize(25u);
                ErrorTexts[static_cast<size_t>(i)].setFillColor(sf::Color::Red);
                ErrorTexts[static_cast<size_t>(i)].setOrigin(ErrorTexts[static_cast<size_t>(i)].getLocalBounds().position + ErrorTexts[static_cast<size_t>(i)].getLocalBounds().size / 2.0f);
                ErrorTexts[static_cast<size_t>(i)].setPosition(sf::Vector2f(static_cast<float>(window.getSize().x) / 2.0f, static_cast<float>(window.getSize().y) / 3.0f + static_cast<float>(i - 1) * 40.0f));
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
                ErrorTexts[static_cast<size_t>(i)].setOrigin(ErrorTexts[static_cast<size_t>(i)].getLocalBounds().position + ErrorTexts[static_cast<size_t>(i)].getLocalBounds().size / 2.0f);
                window.draw(ErrorTexts[static_cast<size_t>(i)]);
            }
            window.display();
        }
        window.close();
        exit(1);
    }

    float resetdiff = 10.0f;
    if (type == TextType::Reset) {
        text.setString("RESET");
        text.setFillColor(sf::Color::White);
        text.setCharacterSize(static_cast<unsigned int>(CharacterSize));
        sf::FloatRect bounds = text.getLocalBounds();
        sf::Vector2f center = bounds.getCenter();
        text.setPosition(sf::Vector2f(static_cast<float>(window.getSize().x) - center.x * 2.0f - resetdiff, 45.0f));
    }
    else if(type == TextType::Settings) {
        text.setString("SETTINGS");
        text.setFillColor(sf::Color::White);
        text.setCharacterSize(static_cast<unsigned int>(CharacterSize));
        sf::FloatRect bounds = text.getLocalBounds();
        sf::Vector2f center = bounds.getCenter();
        text.setPosition(sf::Vector2f(static_cast<float>(window.getSize().x) - center.x * 2.0f - resetdiff, 5.0f));
	}
    else if (type == TextType::FPS) {
        text.setFillColor(sf::Color::Green);
        text.setCharacterSize(static_cast<unsigned int>(CharacterSizeFPS));
        text.setPosition(sf::Vector2f(10.0f, 5.0f));
    }
    else if (type == TextType::Click) {
        text.setString("Click");
        text.setFillColor(sf::Color::White);
        text.setCharacterSize(static_cast<unsigned int>(CharacterSize + 15.f));
        sf::FloatRect bounds = text.getLocalBounds();
        sf::Vector2f center = bounds.getCenter();
        //text.setOrigin(clickText.getLocalBounds().position + clickText.getLocalBounds().size / 2.0f);
        text.setPosition(sf::Vector2f(static_cast<float>(window.getSize().x) / 2.0f, static_cast<float>(window.getSize().y) / 2.0f));
    }
    else if (type == TextType::name) {
        text.setString("Welcome to AutoTCAS");
        text.setFillColor(sf::Color::White);
        text.setCharacterSize(static_cast<unsigned int>(CharacterSize + 50.f));
        sf::FloatRect bounds = text.getLocalBounds();
        sf::Vector2f center = bounds.getCenter();
        text.setPosition(sf::Vector2f(static_cast<float>(window.getSize().x) / 2.0f - center.x, static_cast<float>(window.getSize().y) / 2.0f - 200.0f ));
    }
    else if (type == TextType::TooClose) {
        text.setString("TOO CLOSE");
        text.setFillColor(sf::Color::White);
        text.setCharacterSize(static_cast<unsigned int>(TooCloseCharacterSize));
        sf::FloatRect bounds = text.getLocalBounds();
        sf::Vector2f center = bounds.getCenter();
        //text.setPosition(sf::Vector2f(static_cast<float>(window.getSize().x) / 2.0f - center.x, static_cast<float>(window.getSize().y) / 2.0f - center.y));
	}
    else {
        cout << "ERROR: TextUpdate type does not match up" << endl;
	}
}



void UI::InitializeTextUI(sf::RenderWindow& window, UI& ui) {
    //SETTINGS Text
    sf::Text& settingstext = ui.getSettingsText();
	ui.TextUpdate(settingstext, window, UI::TextType::Settings);

    // Reset BUTTON 
    sf::Text& reset = ui.getResetButton();
    ui.TextUpdate(reset, window, UI::TextType::Reset);

    //FPS display
    sf::Text& fpsText = ui.getFPSDisplay();
    ui.TextUpdate(fpsText, window, UI::TextType::FPS);

    // Clicktext display
    sf::Text& clickText = ui.getClickText();
    ui.TextUpdate(clickText, window, UI::TextType::Click);
	// nameText display
	sf::Text& nameText = ui.getNameText();
	ui.TextUpdate(nameText, window, UI::TextType::name);

    //Too close display
	sf::Text& tooCloseText = ui.getClickText();
	ui.TextUpdate(tooCloseText, window, UI::TextType::TooClose);

}

void UI::GenerateSettingsMenu(sf::RenderWindow& window, UI& ui) {
    //SETTINGS SHAPE
    sf::RectangleShape& settings = ui.getSettings();
    settings.setSize(sf::Vector2f(static_cast<float>(window.getSize().y) - 250.0f, static_cast<float>(window.getSize().y) - 250.0f));
    settings.setFillColor(sf::Color(50, 50, 50, 150));
    settings.setOutlineColor(sf::Color::White);
    settings.setOutlineThickness(0.5f);
    sf::Vector2f center = settings.getGeometricCenter();
    settings.setPosition(sf::Vector2f(static_cast<float>(window.getSize().x) / 2.0f - center.x, static_cast<float>(window.getSize().y) / 2.0f - center.y + 25.0f));
    window.draw(settings);
    
    // Exit Button (fixed position - doesn't scroll)
    sf::RectangleShape& exitButton = ui.getExitButton();
    exitButton.setSize(sf::Vector2f(settings.getSize().x * 0.075f, settings.getSize().y * 0.075f));
    exitButton.setFillColor(sf::Color(200, 0, 0));
    exitButton.setPosition(sf::Vector2f(settings.getGlobalBounds().position.x + settings.getGlobalBounds().size.x - exitButton.getSize().x - 5.0f, settings.getGlobalBounds().position.y + 5.0f));
    window.draw(exitButton);
    
    // Exit Text (fixed position)
    sf::Text& exitText = ui.getExitText();
    exitText.setString("X");
    exitText.setFillColor(sf::Color::White);
    exitText.setCharacterSize(static_cast<unsigned int>(exitButton.getSize().y * 0.9f));
    const sf::FloatRect tb = exitText.getLocalBounds();
    exitText.setOrigin(tb.position + tb.size / 2.0f);
    exitText.setPosition(sf::Vector2f(exitButton.getPosition().x + exitButton.getSize().x * 0.5f, exitButton.getPosition().y + exitButton.getSize().y * 0.5f));
    window.draw(exitText);

    // Pause Text (fixed position)
    sf::Text& pauseText = ui.getPauseText();
    pauseText.setString("**PAUSED**");
    pauseText.setFillColor(sf::Color::White);
    pauseText.setCharacterSize(50u);
    const sf::FloatRect ptb = pauseText.getLocalBounds();
    pauseText.setOrigin(ptb.position + ptb.size / 2.0f);
    const float settingsTop = settings.getGlobalBounds().position.y;
    const float midY = settingsTop * 0.5f;
    const float midX = settings.getPosition().x + settings.getSize().x * 0.5f;
    pauseText.setPosition(sf::Vector2f(midX, midY));
    window.draw(pauseText);


    // SCROLLABLE CONTENT
    float contentAreaTop = exitButton.getGlobalBounds().position.y + 80.0f; // Leave space for header
    float contentAreaHeight = settings.getGlobalBounds().size.y - 120.0f; // Leave space for header/footer
    float startingContentY = contentAreaTop;
    
    
    float currentY = contentAreaTop - scrollOffset;
    
    //Window Settings Text (scrollable)
    sf::Text& windowSettingsText = ui.getWindowSettingsText();
    windowSettingsText.setString("Window Settings (INOP)");
    windowSettingsText.setFillColor(sf::Color::White);
    windowSettingsText.setCharacterSize(static_cast<unsigned int>(settings.getSize().y * 0.05f));
    const sf::FloatRect wstb = windowSettingsText.getLocalBounds();
    windowSettingsText.setOrigin(wstb.position + wstb.size / 2.0f);
    windowSettingsText.setPosition(sf::Vector2f(midX, currentY));
    // Only draw if within visible area
    if (currentY >= contentAreaTop && currentY <= contentAreaTop + contentAreaHeight) {
        window.draw(windowSettingsText);
    }
    currentY += 60.0f; // Space between elements
    
    // WINDOW MODE TEXT (scrollable)
    sf::Text& windowModeText = ui.getWindowModeText();
    windowModeText.setString("Current Window Mode: ");
    windowModeText.setFillColor(sf::Color::White);
    windowModeText.setCharacterSize(static_cast<unsigned int>(settings.getSize().y * 0.05f - 10.0f));
    const sf::FloatRect wmtb = windowModeText.getLocalBounds();
    windowModeText.setOrigin(wmtb.position + wmtb.size / 2.0f);
    windowModeText.setPosition(sf::Vector2f(midX, currentY));

    // Only draw if within visible area
    if (currentY >= contentAreaTop && currentY <= contentAreaTop + contentAreaHeight) {
        window.draw(windowModeText);
    }
    currentY += 100.0f; // Space between elements

    
    // Add more content to test scrolling
    for (int i = 0; i < 10; ++i) {
        sf::Text testText{ ui.edges };
        testText.setString("Test Option " + std::to_string(i + 1));
        testText.setFillColor(sf::Color::White);
        testText.setCharacterSize(30u);
        const sf::FloatRect ttb = testText.getLocalBounds();
        testText.setOrigin(ttb.position + ttb.size / 2.0f);
        testText.setPosition(sf::Vector2f(midX, currentY));
        
        // Only draw if within visible area
        if (currentY >= contentAreaTop && currentY <= contentAreaTop + contentAreaHeight) {
            window.draw(testText);
        }
        currentY += 60.0f; // Space between elements
    }

    // Calculate total content height properly
    float totalContentHeight = (currentY + scrollOffset) - startingContentY;
    maxScrollOffset = std::max(0.0f, totalContentHeight - contentAreaHeight);

    // Clamp scroll offset - prevent scrolling above the content area top
    float minScrollOffset = 0.0f;
    scrollOffset = std::max(minScrollOffset, std::min(scrollOffset, maxScrollOffset));
}

void UI::DrawAndOrAnimateText(sf::RenderWindow& window, sf::Time dt, UI& ui) {
	//Settings
    if(!ui.showClickMessage) {
        ui.TextUpdate(ui.settingsText, window, TextType::Settings);
        window.draw(ui.settingsText);
	}

    // Draw settings menu only if open
    if (ui.settingsMenuOpen) {
        ui.GenerateSettingsMenu(window, ui);
    }

    // Reset Button
    if (!ui.showClickMessage) {
        ui.TextUpdate(ui.reset, window, TextType::Reset);
        window.draw(ui.reset);
    }

    //FPS display
    frameTime += dt.asSeconds();
    frameCount++;
    if (frameTime >= 1.0f) {
        float fps = frameCount / frameTime;
        fpsText.setString("FPS: " + std::to_string(static_cast<int>(fps)));
        frameTime = 0.0f;
        frameCount = 0.0f;
    }
    if (!ui.showClickMessage) {
        ui.TextUpdate(ui.fpsText, window, TextType::FPS);
        window.draw(ui.fpsText);
    }


	//CLICK MESSAGE
    if (showClickMessage) {
        charTimer += dt.asSeconds();
        if (visibleChars < fullClickMessage.size() && charTimer >= charInterval) {
            ++visibleChars;
            charTimer = 0.0f;
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
                dotTimer = 0.0f;
            }
            std::string dots(static_cast<size_t>(dotCount), '.');
            displayText += dots;
        }
		ui.TextUpdate(ui.clickText, window, UI::TextType::Click);
        clickText.setString(displayText);
		// Always set origin from the local bounds to keep it centered while the size inscreases
        clickText.setOrigin(clickText.getLocalBounds().position + clickText.getLocalBounds().size / 2.0f);


		ui.TextUpdate(ui.nameText, window, UI::TextType::name);

        // draw a semi-transparent overlay.
        sf::RectangleShape overlay(sf::Vector2f(static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y)));
        overlay.setFillColor(sf::Color(0, 0, 0, 128));
        
        
        
        window.draw(overlay);
        window.draw(clickText);
		window.draw(nameText);
    }
   

    //TOO CLOSE MESSAGES
    // update all active tooclosetexts using vectors
    for (size_t i = 0; i < tooCloseTimers.size();) {
        tooCloseTimers[i] += dt.asSeconds();
        if (tooCloseTimers[i] >= tooCloseDurations[i]) {
            // Remove expired message by erasing from all four vectors
            tooCloseTexts.erase(tooCloseTexts.begin() + static_cast<ptrdiff_t>(i));
            tooCloseTimers.erase(tooCloseTimers.begin() + static_cast<ptrdiff_t>(i));
            tooCloseDurations.erase(tooCloseDurations.begin() + static_cast<ptrdiff_t>(i));
            tooClosePositions.erase(tooClosePositions.begin() + static_cast<ptrdiff_t>(i));
        }
        else {
            ++i;
        }
    }

    for (size_t i = 0; i < tooCloseTexts.size(); ++i) {
        ui.TextUpdate(tooCloseTexts[i], window, TextType::TooClose);
        sf::FloatRect bounds = tooCloseTexts[i].getLocalBounds();
        sf::Vector2f center = bounds.getCenter();
        tooCloseTexts[i].setPosition(sf::Vector2f(tooClosePositions[i].x - center.x, tooClosePositions[i].y - center.y));
        
        window.draw(tooCloseTexts[i]);
    }
}