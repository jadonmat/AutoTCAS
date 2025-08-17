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
    
    // Get current window size instead of desktop mode
    sf::Vector2u windowSize = window.getSize();
    
    // Calculate scaling factors based on window size
    // Using 1440p as the base reference resolution
    float scaleX = static_cast<float>(windowSize.x) / 2560.0f;
    float scaleY = static_cast<float>(windowSize.y) / 1440.0f;
    float scale = std::min(scaleX, scaleY); // Use the smaller scale to maintain aspect ratio
    
    // Base character sizes (for 1920x1080)
    float baseCharacterSize = 50.0f;
    float baseFPSSize = 30.0f;
    float baseTooCloseSize = 8.0f;
    
    // Calculate scaled sizes
    float CharacterSize = baseCharacterSize * scale;
    float CharacterSizeFPS = baseFPSSize * scale;
    float TooCloseCharacterSize = baseTooCloseSize; //* scale;
    
    float resetdiff = 10.0f * scale; // Scale the offset too
    
    if (type == TextType::Reset) {
        text.setString("RESET");
        text.setFillColor(sf::Color::White);
        text.setCharacterSize(static_cast<unsigned int>(CharacterSize));
        sf::FloatRect bounds = text.getLocalBounds();
        sf::Vector2f center = bounds.getCenter();
        text.setPosition(sf::Vector2f(static_cast<float>(window.getSize().x) - center.x * 2.0f - resetdiff, 70.0f * scale));
    }
    else if(type == TextType::Settings) {
        text.setString("SETTINGS");
        text.setFillColor(sf::Color::White);
        text.setCharacterSize(static_cast<unsigned int>(CharacterSize));
        sf::FloatRect bounds = text.getLocalBounds();
        sf::Vector2f center = bounds.getCenter();
        text.setPosition(sf::Vector2f(static_cast<float>(window.getSize().x) - center.x * 2.0f - resetdiff, 5.0f * scale));
    }
    else if (type == TextType::FPS) {
        text.setFillColor(sf::Color::Green);
        text.setCharacterSize(static_cast<unsigned int>(CharacterSizeFPS));
        text.setPosition(sf::Vector2f(10.0f * scale, 5.0f * scale));
    }
    else if (type == TextType::Click) {
        text.setString("Click");
        text.setFillColor(sf::Color::White);
        text.setCharacterSize(static_cast<unsigned int>(CharacterSize + 15.0f * scale));
        sf::FloatRect bounds = text.getLocalBounds();
        sf::Vector2f center = bounds.getCenter();
        text.setPosition(sf::Vector2f(static_cast<float>(window.getSize().x) / 2.0f, static_cast<float>(window.getSize().y) / 2.0f));
    }
    else if (type == TextType::name) {
        text.setString("Welcome to AutoTCAS");
        text.setFillColor(sf::Color::White);
        text.setCharacterSize(static_cast<unsigned int>(CharacterSize + 50.0f * scale));
        sf::FloatRect bounds = text.getLocalBounds();
        sf::Vector2f center = bounds.getCenter();
        text.setPosition(sf::Vector2f(static_cast<float>(window.getSize().x) / 2.0f - center.x, static_cast<float>(window.getSize().y) / 2.0f - 200.0f * scale));
    }
    else if (type == TextType::TooClose) {
        text.setString("TOO CLOSE");
        text.setFillColor(sf::Color::White);
        text.setCharacterSize(static_cast<unsigned int>(TooCloseCharacterSize));
        sf::FloatRect bounds = text.getLocalBounds();
        sf::Vector2f center = bounds.getCenter();
    }
    else {
        //cout << "ERROR: TextUpdate type does not match up" << endl;
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