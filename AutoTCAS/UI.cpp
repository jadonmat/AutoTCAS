//Seperate class, not related to the aircraft inherentence structure.
#include <iostream>
#include <vector>
#include "UI.h"
using namespace std;

UI::UI() {
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
    currentFPSString = "FPS: 0";
    edges = getedgesFont();
    pixellari = getpixellariFont();
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

sf::RectangleShape& UI::getExitButton() {
    return exitButton; 
}

sf::Text& UI::getResetButton() {
    return reset; 
}

void UI::GenerateIntro(sf::RenderWindow& window, UI& ui, sf::Time dt) {
    // Get current window size
    sf::Vector2u windowSize = window.getSize();

    // Calculate scaling factors based on window size
    // Using 1440p as the base reference resolution
    float scaleX = static_cast<float>(windowSize.x) / 2560.0f;
    float scaleY = static_cast<float>(windowSize.y) / 1440.0f;
    float rawScale = std::min(scaleX, scaleY); // Use the smaller scale to maintain aspect ratio

    // Clamp scale to minimum and maximum values
    float scale = std::clamp(rawScale, MIN_SCALE, MAX_SCALE);

    // Base character sizes
    float baseCharacterSize = 50.0f;

    // Calculate scaled sizes
    float CharacterSize = baseCharacterSize * scale;

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
    sf::Text clickText{ edges };
    clickText.setString("Click");
    clickText.setFillColor(sf::Color::White);
    clickText.setCharacterSize(static_cast<unsigned int>(CharacterSize + 10.0f * scale));
    clickText.setPosition(sf::Vector2f(static_cast<float>(window.getSize().x) / 2.0f, static_cast<float>(window.getSize().y) / 2.0f));
    clickText.setString(displayText);
    // Always set origin from the local bounds to keep it centered while the size inscreases
    clickText.setOrigin(clickText.getLocalBounds().position + clickText.getLocalBounds().size / 2.0f);

    sf::Text nameText{ edges };
    nameText.setString("Welcome to AutoTCAS");
    nameText.setFillColor(sf::Color::White);
    nameText.setCharacterSize(static_cast<unsigned int>(CharacterSize + 50.0f * scale));
    sf::FloatRect boundsName = nameText.getLocalBounds();
    sf::Vector2f centerName = boundsName.getCenter();
    nameText.setPosition(sf::Vector2f(static_cast<float>(window.getSize().x) / 2.0f - centerName.x, static_cast<float>(window.getSize().y) / 2.0f - 300.0f * scale));

    // draw a semi-transparent overlay.
    sf::RectangleShape overlay(sf::Vector2f(static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y)));
    overlay.setFillColor(sf::Color(0, 0, 0, 128));



    window.draw(overlay);
    window.draw(clickText);
    window.draw(nameText);

}

void UI::GenerateFPS(sf::RenderWindow& window, UI& ui, sf::Time dt) {
    // Get current window size
    sf::Vector2u windowSize = window.getSize();

    // Calculate scaling factors based on window size
    // Using 1440p as the base reference resolution
    float scaleX = static_cast<float>(windowSize.x) / 2560.0f;
    float scaleY = static_cast<float>(windowSize.y) / 1440.0f;
    float rawScale = std::min(scaleX, scaleY); // Use the smaller scale to maintain aspect ratio

    // Clamp scale to minimum and maximum values
    float scale = std::clamp(rawScale, MIN_SCALE, MAX_SCALE);
    float scale_fps = std::clamp(rawScale, MIN_SCALE, MAX_SCALE_FPS);

    // Base character sizes
    float baseFPSSize = 30.0f;

    // Calculate scaled sizes
    float CharacterSizeFPS = baseFPSSize * scale_fps;

    // Update FPS calculation
    frameTime += dt.asSeconds();
    frameCount++;
    if (frameTime >= 1.0f) {
        float fps = frameCount / frameTime;
        currentFPSString = "FPS: " + std::to_string(static_cast<int>(fps));
        frameTime = 0.0f;
        frameCount = 0.0f;
    }

    // Create and draw FPS text using the stored string
    sf::Text fpsText{ pixellari };
    fpsText.setString(currentFPSString);
    fpsText.setFillColor(sf::Color::Green);
    fpsText.setCharacterSize(static_cast<unsigned int>(CharacterSizeFPS));
    fpsText.setPosition(sf::Vector2f(10.0f * scale, 5.0f * scale));
    window.draw(fpsText);
}


void UI::GenerateSettingsMenu(sf::RenderWindow& window, UI& ui) {
    // Get current window size
    sf::Vector2u windowSize = window.getSize();

    // Calculate scaling factors based on window size
    // Using 1440p as the base reference resolution (matching TextUpdate)
    float scaleX = static_cast<float>(windowSize.x) / 2560.0f;
    float scaleY = static_cast<float>(windowSize.y) / 1440.0f;
    float rawScale = std::min(scaleX, scaleY); // Use the smaller scale to maintain aspect ratio
    
    // Clamp scale to minimum and maximum values
    float scale = std::clamp(rawScale, MIN_SCALE, MAX_SCALE);
	float scale_settings = std::clamp(rawScale, MIN_SCALE, MAX_SCALE_SETTINGS);

    // Base sizes for scaling
    float baseMenuWidth = 1500.0f;
    float baseMenuHeight = 500.0f;
    float baseSpacing = 60.0f;
    float baseLargeSpacing = 100.0f;
    float baseHeaderOffset = 80.0f;
    float baseMargin = 120.0f;
    float baseFontSize = 100.0f;
    float baseSmallFontSize = 30.0f;

    //SETTINGS SHAPE - Calculate proposed size first
    float proposedWidth = static_cast<float>(window.getSize().x) - baseMenuWidth * scale * 0.75f;
    float proposedHeight = static_cast<float>(window.getSize().y) - baseMenuHeight * scale * 0.75f;
    
    // Apply maximum size constraints
    float finalWidth = std::min(proposedWidth, MAX_SETTINGS_WIDTH);
    //float finalHeight = std::min(proposedHeight, MAX_SETTINGS_HEIGHT);
    
    sf::RectangleShape& settings = ui.getSettings();
    settings.setSize(sf::Vector2f(finalWidth, proposedHeight));
    settings.setFillColor(sf::Color(50, 50, 50, 150));
    settings.setOutlineColor(sf::Color::White);
    settings.setOutlineThickness(0.5f * scale);
    sf::Vector2f center = settings.getGeometricCenter();
    settings.setPosition(sf::Vector2f(static_cast<float>(window.getSize().x) / 2.0f - center.x, static_cast<float>(window.getSize().y) / 2.0f - center.y + 25.0f * scale));
    window.draw(settings);
    
    // Exit Button (fixed position - doesn't scroll)
    sf::RectangleShape& exitButton = ui.getExitButton();
    exitButton.setSize(sf::Vector2f(settings.getSize().x * 0.075f, settings.getSize().y * 0.075f));
    exitButton.setFillColor(sf::Color(200, 0, 0));
    exitButton.setPosition(sf::Vector2f(settings.getGlobalBounds().position.x + settings.getGlobalBounds().size.x - exitButton.getSize().x - 5.0f * scale, settings.getGlobalBounds().position.y + 5.0f * scale));
    window.draw(exitButton);
    
    // Exit Text (fixed position)
    sf::Text exitText{ edges };
    exitText.setString("X");
    exitText.setFillColor(sf::Color::White);
    exitText.setCharacterSize(static_cast<unsigned int>(exitButton.getSize().y * 0.9f));
    const sf::FloatRect tb = exitText.getLocalBounds();
    exitText.setOrigin(tb.position + tb.size / 2.0f);
    exitText.setPosition(sf::Vector2f(exitButton.getPosition().x + exitButton.getSize().x * 0.5f, exitButton.getPosition().y + exitButton.getSize().y * 0.5f));
    window.draw(exitText);

    // Pause Text (fixed position)
    sf::Text pauseText{ edges };
    pauseText.setString("**PAUSED**");
    pauseText.setFillColor(sf::Color::White);
    pauseText.setCharacterSize(static_cast<unsigned int>(baseFontSize * scale));
    const sf::FloatRect ptb = pauseText.getLocalBounds();
    pauseText.setOrigin(ptb.position + ptb.size / 2.0f);
    const float settingsTop = settings.getGlobalBounds().position.y;
    const float midY = settingsTop * 0.5f;
    const float midX = settings.getPosition().x + settings.getSize().x * 0.5f;
    pauseText.setPosition(sf::Vector2f(midX, midY));
    window.draw(pauseText);

    // Settings Title Text (fixed position)
    sf::Text settingsTitle{ edges };
    settingsTitle.setString("SETTINGS MENU");
    settingsTitle.setFillColor(sf::Color::White);
    settingsTitle.setCharacterSize(static_cast<unsigned int>(baseFontSize * scale * 1.5f));
    const sf::FloatRect stb = settingsTitle.getLocalBounds();
    settingsTitle.setOrigin(stb.position + stb.size / 2.0f);
    settingsTitle.setPosition(sf::Vector2f(midX, settings.getPosition().y + baseHeaderOffset * scale));
    //window.draw(settingsTitle);

    // SCROLLABLE CONTENT
    float contentAreaTop = exitButton.getGlobalBounds().position.y + baseHeaderOffset * scale; // Scale header offset
    float contentAreaHeight = settings.getGlobalBounds().size.y - baseMargin * scale; // Scale margin
    float startingContentY = contentAreaTop;
    
    // Calculate total content height first (without drawing) - scale all spacing
    float tempCurrentY = contentAreaTop;
    tempCurrentY += baseSpacing * scale; // Window Settings Text height
    tempCurrentY += baseLargeSpacing * scale; // Window Mode Text height
    tempCurrentY += 10 * baseSpacing * scale; // Test options height
    
    float totalContentHeight = tempCurrentY - startingContentY;
    maxScrollOffset = std::max(0.0f, totalContentHeight - contentAreaHeight);

    // Clamp scroll offset BEFORE calculating positions
    float minScrollOffset = 0.0f;
    scrollOffset = std::max(minScrollOffset, std::min(scrollOffset, maxScrollOffset));
    
    // Now calculate positions with clamped scroll offset
    float currentY = contentAreaTop - scrollOffset;
    

    //Window Settings Text (scrollable)
    sf::Text windowSettingsText{ edges };
    windowSettingsText.setString("Window Settings (INOP)");
    windowSettingsText.setFillColor(sf::Color::White);
    windowSettingsText.setCharacterSize(static_cast<unsigned int>(baseFontSize * scale * 0.6f)); // Scale font size
    const sf::FloatRect wstb = windowSettingsText.getLocalBounds();
    windowSettingsText.setOrigin(wstb.position + wstb.size / 2.0f);
    windowSettingsText.setPosition(sf::Vector2f(midX, currentY));
    // Only draw if within visible area
    if (currentY >= contentAreaTop && currentY <= contentAreaTop + contentAreaHeight) {
        window.draw(windowSettingsText);
    }
    currentY += baseSpacing * scale; // Scale spacing between elements
    
    // WINDOW MODE TEXT (scrollable)
    sf::Text windowModeText{ edges };
    windowModeText.setString("Current Window Mode: ");
    windowModeText.setFillColor(sf::Color::White);
    windowModeText.setCharacterSize(static_cast<unsigned int>(baseSmallFontSize * scale)); // Scale font size
    const sf::FloatRect wmtb = windowModeText.getLocalBounds();
    windowModeText.setOrigin(wmtb.position + wmtb.size / 2.0f);
    windowModeText.setPosition(sf::Vector2f(midX, currentY));

    // Only draw if within visible area
    if (currentY >= contentAreaTop && currentY <= contentAreaTop + contentAreaHeight) {
        window.draw(windowModeText);
    }
    currentY += baseLargeSpacing * scale; // Scale spacing between elements

    // Add more content to test scrolling
    for (int i = 0; i < 10; ++i) {
        sf::Text testText{ ui.edges };
        testText.setString("Test Option " + std::to_string(i + 1));
        testText.setFillColor(sf::Color::White);
        testText.setCharacterSize(static_cast<unsigned int>(baseSmallFontSize * scale)); // Scale test text font
        const sf::FloatRect ttb = testText.getLocalBounds();
        testText.setOrigin(ttb.position + ttb.size / 2.0f);
        testText.setPosition(sf::Vector2f(midX, currentY));
        
        // Only draw if within visible area
        if (currentY >= contentAreaTop && currentY <= contentAreaTop + contentAreaHeight) {
            window.draw(testText);
        }
        currentY += baseSpacing * scale; // Scale spacing between elements
    }
}

void UI::DrawUI(sf::RenderWindow& window, sf::Time dt, UI& ui) {
    // Get current window size
    sf::Vector2u windowSize = window.getSize();

    // Calculate scaling factors based on window size
    // Using 1440p as the base reference resolution
    float scaleX = static_cast<float>(windowSize.x) / 2560.0f;
    float scaleY = static_cast<float>(windowSize.y) / 1440.0f;
    float rawScale = std::min(scaleX, scaleY); // Use the smaller scale to maintain aspect ratio

    // Clamp scale to minimum and maximum values
    float scale = std::clamp(rawScale, MIN_SCALE, MAX_SCALE);
    float scale_fps = std::clamp(rawScale, MIN_SCALE, MAX_SCALE_FPS);

    // Base character sizes
    float baseCharacterSize = 50.0f;
    float baseFPSSize = 30.0f;
    float baseTooCloseSize = 8.0f;

    // Calculate scaled sizes
    float CharacterSize = baseCharacterSize * scale;
    float CharacterSizeFPS = baseFPSSize * scale_fps;
    float TooCloseCharacterSize = baseTooCloseSize; //* scale;
    
    float resetdiff = 10.0f * scale; // Scale the offset too
    

    //SETTINGS
    if(!ui.showClickMessage) {
        sf::Text& settingstext = ui.getSettingsText();
        settingstext.setString("SETTINGS");
        settingstext.setFillColor(sf::Color::White);
        settingstext.setCharacterSize(static_cast<unsigned int>(CharacterSize));
        sf::FloatRect bounds = settingstext.getLocalBounds();
        sf::Vector2f center = bounds.getCenter();
        settingstext.setPosition(sf::Vector2f(static_cast<float>(window.getSize().x) - center.x * 2.0f - resetdiff, 5.0f * scale));
        window.draw(settingsText);
	}
    // Draw settings menu only if open
    if (ui.settingsMenuOpen) {
        ui.GenerateSettingsMenu(window, ui);
    }


	// RESET BUTTON
    if (!ui.showClickMessage) {
        sf::Text& reset = ui.getResetButton();
        reset.setFont(edges);
        reset.setString("RESET");
        reset.setFillColor(sf::Color::White);
        reset.setCharacterSize(static_cast<unsigned int>(CharacterSize));
        sf::FloatRect bounds = reset.getLocalBounds();
        sf::Vector2f center = bounds.getCenter();
        reset.setPosition(sf::Vector2f(static_cast<float>(window.getSize().x) - center.x * 2.0f - resetdiff, 70.0f * scale));
        window.draw(reset);
    }


	// FPS DISPLAY
    if (!ui.showClickMessage) {
		GenerateFPS(window, ui, dt);
    }


	//INTRO
    if (showClickMessage) {
		GenerateIntro(window, ui, dt);
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
        tooCloseTexts[i].setString("TOO CLOSE");
        tooCloseTexts[i].setFillColor(sf::Color::White);
        tooCloseTexts[i].setCharacterSize(static_cast<unsigned int>(TooCloseCharacterSize));
        sf::FloatRect bounds = tooCloseTexts[i].getLocalBounds();
        sf::Vector2f centerClose = bounds.getCenter();
        tooCloseTexts[i].setPosition(sf::Vector2f(tooClosePositions[i].x - centerClose.x, tooClosePositions[i].y - centerClose.y));
        
        window.draw(tooCloseTexts[i]);
    }
}