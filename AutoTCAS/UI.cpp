//Seperate class, not related to the aircraft inherentence structure.
#include <iostream>
#include <vector>
#include "UI.h"
#include "Window.h"
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
    resetTextTimer = 0.0f;
    resetTextDuration = 2.0f;
    showResetText = false;
    resetButtonPressed = false;
    edges = getedgesFont();
    pixellari = getpixellariFont();
    arial = getarialFont();
}


sf::Font UI::getedgesFont() const {
    sf::Font edgesFont("Fonts/Edges.ttf");
    return edgesFont;
}

sf::Font UI::getpixellariFont() const {
	sf::Font pixellariFont("Fonts/Pixellari.ttf");
	return pixellariFont;
}

sf::Font UI::getarialFont() const {
    sf::Font InterFont("Fonts/Inter_18pt-ExtraBold.ttf");
	return InterFont;
}

sf::CircleShape& UI::getSettingsIconCircle() {
    return settingsIconCircle;
}

sf::RectangleShape& UI::getSettingsIconTooth() {
    return settingsIconTooth;
}


sf::RectangleShape& UI::getSettings() {
    return settings; 
}

sf::RectangleShape& UI::getExitButton() {
    return exitButton; 
}

sf::CircleShape& UI::getResetIconCircle() {
    return resetIconCircle;
}

sf::ConvexShape& UI::getResetIconArrow() {
    return resetIconArrow;
}

sf::RectangleShape& UI::getResetIconRectangle() {
	return resetIconRectangle;
}


sf::RectangleShape& UI::getWindowedButton() {
    return windowedButton;
}

sf::RectangleShape& UI::getFullscreenButton() {
    return fullscreenButton;
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


void UI::GenerateSettingsMenu(sf::RenderWindow& window, UI& ui, const Window& windowObj) {
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
	float baseMenuWidth = 1700.0f; // lowers the width of the settings menu
	float baseMenuHeight = 500.0f; // lowers the height of the settings menu
	float baseSpacing = 60.0f; // Spacing between elements
	float baseLargeSpacing = 100.0f; // Large spacing between sections
	float baseMargin = 120.0f; // Margin for the settings menu
	float baseFontSize = 80.0f; // Base font size for text
	float baseSmallFontSize = 30.0f; // Base font size for smaller text (sub sections)
    float baseButtonWidth = 200.0f; // Base button width
    float baseButtonHeight = 50.0f; // Base button height
    float baseButtonSpacing = 40.0f; // Base spacing between buttons

    //SETTINGS SHAPE - Calculate proposed size first
    float proposedWidth = static_cast<float>(window.getSize().x) - baseMenuWidth * scale * 0.75f;
    float proposedHeight = static_cast<float>(window.getSize().y) - baseMenuHeight * scale * 0.75f;
    
    // When window is narrow, limit the height more aggressively
    float dynamicMaxHeight = std::min(MAX_SETTINGS_HEIGHT, static_cast<float>(windowSize.x) * 0.5f);
    
    // Apply min and max size constraints for width
    float finalWidth = std::clamp(proposedWidth, MIN_SETTINGS_WIDTH, MAX_SETTINGS_WIDTH);
	float finalHeight = std::min(proposedHeight, dynamicMaxHeight);
    
    sf::RectangleShape& settings = ui.getSettings();
    settings.setSize(sf::Vector2f(finalWidth, finalHeight));
    settings.setFillColor(sf::Color(50, 50, 50, 150));
    settings.setOutlineColor(sf::Color::White);
    settings.setOutlineThickness(0.75f * scale);
    sf::Vector2f center = settings.getGeometricCenter();
    settings.setPosition(sf::Vector2f(static_cast<float>(window.getSize().x) / 2.0f - center.x, static_cast<float>(window.getSize().y) / 2.0f - center.y + 25.0f * scale));
    window.draw(settings);
    
    // Exit Button (fixed position - doesn't scroll)
    sf::RectangleShape& exitButton = ui.getExitButton();
    exitButton.setSize(sf::Vector2f(settings.getSize().x * 0.075f, settings.getSize().y * 0.075f));
    exitButton.setFillColor(sf::Color(200, 0, 0));
    exitButton.setPosition(sf::Vector2f(settings.getGlobalBounds().position.x + settings.getGlobalBounds().size.x - exitButton.getSize().x - 5.0f * scale, settings.getGlobalBounds().position.y + 5.0f * scale));
    
    // Calculate header height based on exit button position
    float headerHeight = exitButton.getGlobalBounds().position.y + exitButton.getGlobalBounds().size.y - settings.getGlobalBounds().position.y + 40.0f * scale;
    
    // Header background (fixed position)
    sf::RectangleShape header;
    header.setSize(sf::Vector2f(settings.getSize().x, headerHeight));
    header.setFillColor(sf::Color(70, 70, 70, 200));
    header.setPosition(settings.getPosition());
    window.draw(header);
    
    // Redraw settings outline to appear on top of header
    sf::RectangleShape settingsOutline;
    settingsOutline.setSize(settings.getSize());
    settingsOutline.setPosition(settings.getPosition());
    settingsOutline.setFillColor(sf::Color::Transparent);
    settingsOutline.setOutlineColor(sf::Color::White);
    settingsOutline.setOutlineThickness(0.5f * scale);
    window.draw(settingsOutline);
    
    // Draw exit button on top of header
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

    // Settings Title Text (fixed position in header)
    sf::Text settingsTitle{ edges };
    settingsTitle.setString("SETTINGS MENU");
    settingsTitle.setFillColor(sf::Color::White);
    // Scale font size based on header height
    float titleFontSize = headerHeight * 0.8f;
    settingsTitle.setCharacterSize(static_cast<unsigned int>(titleFontSize));
    const sf::FloatRect stb = settingsTitle.getLocalBounds();
    settingsTitle.setOrigin(stb.position + stb.size / 2.0f);
    // Center the title vertically within the header
    float headerCenterY = header.getPosition().y + header.getSize().y * 0.5f;
    settingsTitle.setPosition(sf::Vector2f(midX, headerCenterY));
    window.draw(settingsTitle);

    // SCROLLABLE CONTENT starts after the header
    float contentAreaTop = header.getPosition().y + header.getSize().y;
    float contentAreaHeight = settings.getGlobalBounds().size.y - headerHeight;
    
    // Add some padding after the header
    float contentPadding = 30.0f * scale;
    contentAreaTop += contentPadding;
    contentAreaHeight -= contentPadding * 2.0f; // Subtract padding from both top and bottom
    
    // Define strict boundaries for content visibility
    float contentVisibleTop = contentAreaTop;
    float contentVisibleBottom = contentAreaTop + contentAreaHeight;
    
    // Calculate total content height first (without drawing) - scale all spacing
    float tempCurrentY = 0.0f; // Start from 0 for relative calculation
    tempCurrentY += baseSpacing * scale; // Window Settings Text height
    tempCurrentY += baseSpacing * scale; // Space after Window Settings
    tempCurrentY += baseSmallFontSize * scale; // Window Mode Text height (approximate)
    tempCurrentY += baseSpacing * scale; // Space after Window Mode
    tempCurrentY += baseButtonHeight * scale; // Button height
    tempCurrentY += baseLargeSpacing * scale; // Space after buttons
    tempCurrentY += 10 * (baseSmallFontSize * scale + baseSpacing * scale); // Test options height
    
    float totalContentHeight = tempCurrentY;
    maxScrollOffset = std::max(0.0f, totalContentHeight - contentAreaHeight);

    // Clamp scroll offset BEFORE calculating positions
    float minScrollOffset = 0.0f;
    scrollOffset = std::max(minScrollOffset, std::min(scrollOffset, maxScrollOffset));
    
    // Now calculate positions with clamped scroll offset
    float currentY = contentAreaTop - scrollOffset; // Start content positioning
    

    //Window Settings Text (scrollable)
    sf::Text windowSettingsText{ edges };
    windowSettingsText.setString("Window Settings:");
    windowSettingsText.setFillColor(sf::Color::White);
    windowSettingsText.setCharacterSize(static_cast<unsigned int>(baseFontSize * scale * 0.60f)); // Scale font size
    const sf::FloatRect wstb = windowSettingsText.getLocalBounds();
    windowSettingsText.setOrigin(wstb.position + wstb.size / 2.0f);
    windowSettingsText.setPosition(sf::Vector2f(midX, currentY));
    // Only draw if within strict visible area bounds
    if (currentY >= contentVisibleTop && currentY <= contentVisibleBottom) {
        window.draw(windowSettingsText);
    }
    currentY += baseSpacing * scale; // Scale spacing between elements
    
    // WINDOW MODE TEXT (scrollable) - Updated to show actual window mode
    sf::Text windowModeText{ edges };
    std::string windowModeString = "Current Window Mode: " + windowObj.getCurrentWindowModeString();
    windowModeText.setString(windowModeString);
    windowModeText.setFillColor(sf::Color::White);
    windowModeText.setCharacterSize(static_cast<unsigned int>(baseSmallFontSize * scale)); // Scale font size
    const sf::FloatRect wmtb = windowModeText.getLocalBounds();
    windowModeText.setOrigin(wmtb.position + wmtb.size / 2.0f);
    windowModeText.setPosition(sf::Vector2f(midX, currentY));

    // Only draw if within strict visible area bounds
    if (currentY >= contentVisibleTop && currentY <= contentVisibleBottom) {
        window.draw(windowModeText);
    }
    currentY += baseSpacing * scale; // Scale spacing between elements

    // Window Mode Buttons (scrollable)
    float buttonWidth = baseButtonWidth * scale;
    float buttonHeight = baseButtonHeight * scale;
    float buttonSpacing = baseButtonSpacing * scale;
    
    // Calculate positions for side-by-side buttons
    float totalButtonWidth = (buttonWidth * 2) + buttonSpacing;
    float leftButtonX = midX - (totalButtonWidth / 2.0f);
    float rightButtonX = leftButtonX + buttonWidth + buttonSpacing;

    // Windowed Button
    sf::RectangleShape& windowedButton = ui.getWindowedButton();
    windowedButton.setSize(sf::Vector2f(buttonWidth, buttonHeight));
    // Highlight current mode
    if (!windowObj.isFullscreen) {
        windowedButton.setFillColor(sf::Color(0, 150, 0)); // Green for active
    } else {
        windowedButton.setFillColor(sf::Color(100, 100, 100)); // Gray for inactive
    }
    windowedButton.setOutlineColor(sf::Color::White);
    windowedButton.setOutlineThickness(2.0f * scale);
    windowedButton.setPosition(sf::Vector2f(leftButtonX, currentY - (buttonHeight / 2.0f)));

    // Only draw if within strict visible area bounds
    if (currentY >= contentVisibleTop && currentY <= contentVisibleBottom) {
        window.draw(windowedButton);
        
        // Windowed Button Text
        sf::Text windowedText{ edges };
        windowedText.setString("Windowed");
        windowedText.setFillColor(sf::Color::White);
        windowedText.setCharacterSize(static_cast<unsigned int>(baseSmallFontSize * scale * 0.8f));
        const sf::FloatRect wtb = windowedText.getLocalBounds();
        windowedText.setOrigin(wtb.position + wtb.size / 2.0f);
        windowedText.setPosition(sf::Vector2f(windowedButton.getPosition().x + windowedButton.getSize().x / 2.0f, windowedButton.getPosition().y + windowedButton.getSize().y / 2.0f));
        window.draw(windowedText);
    }

    // Fullscreen Button
    sf::RectangleShape& fullscreenButton = ui.getFullscreenButton();
    fullscreenButton.setSize(sf::Vector2f(buttonWidth, buttonHeight));
    // Highlight current mode
    if (windowObj.isFullscreen) {
        fullscreenButton.setFillColor(sf::Color(0, 150, 0)); // Green for active
    } else {
        fullscreenButton.setFillColor(sf::Color(100, 100, 100)); // Gray for inactive
    }
    fullscreenButton.setOutlineColor(sf::Color::White);
    fullscreenButton.setOutlineThickness(2.0f * scale);
    fullscreenButton.setPosition(sf::Vector2f(rightButtonX, currentY - (buttonHeight / 2.0f)));

    // Only draw if within strict visible area bounds
    if (currentY >= contentVisibleTop && currentY <= contentVisibleBottom) {
        window.draw(fullscreenButton);
        
        // Fullscreen Button Text
        sf::Text fullscreenText{ edges };
        fullscreenText.setString("Fullscreen");
        fullscreenText.setFillColor(sf::Color::White);
        fullscreenText.setCharacterSize(static_cast<unsigned int>(baseSmallFontSize * scale * 0.8f));
        const sf::FloatRect ftb = fullscreenText.getLocalBounds();
        fullscreenText.setOrigin(ftb.position + ftb.size / 2.0f);
        fullscreenText.setPosition(sf::Vector2f(fullscreenButton.getPosition().x + fullscreenButton.getSize().x / 2.0f, fullscreenButton.getPosition().y + fullscreenButton.getSize().y / 2.0f));
        window.draw(fullscreenText);
    }

    currentY += baseLargeSpacing * scale; // Scale spacing between elements

	sf::Text graphicsSettingsText{ edges };
	graphicsSettingsText.setString("Graphics Settings: (INOP)");
	graphicsSettingsText.setFillColor(sf::Color::White);
	graphicsSettingsText.setCharacterSize(static_cast<unsigned int>(baseFontSize * scale * 0.6f)); // Scale font size
	const sf::FloatRect gstb = graphicsSettingsText.getLocalBounds();
	graphicsSettingsText.setOrigin(gstb.position + gstb.size / 2.0f);
	graphicsSettingsText.setPosition(sf::Vector2f(midX, currentY));

	// Only draw if within strict visible area bounds
	if (currentY >= contentVisibleTop && currentY <= contentVisibleBottom) {
		window.draw(graphicsSettingsText);
	}
	currentY += baseLargeSpacing * scale; // Scale spacing between elements

	sf::Text UtilitiesSettingsText{ edges };
	UtilitiesSettingsText.setString("Utilities Settings: (INOP)");
	UtilitiesSettingsText.setFillColor(sf::Color::White);
	UtilitiesSettingsText.setCharacterSize(static_cast<unsigned int>(baseFontSize * scale * 0.6f)); // Scale font size
	const sf::FloatRect ustb = UtilitiesSettingsText.getLocalBounds();
	UtilitiesSettingsText.setOrigin(ustb.position + ustb.size / 2.0f);
	UtilitiesSettingsText.setPosition(sf::Vector2f(midX, currentY));
	// Only draw if within strict visible area bounds
	if (currentY >= contentVisibleTop && currentY <= contentVisibleBottom) {
		window.draw(UtilitiesSettingsText);
	}
	currentY += baseLargeSpacing * scale; // Scale spacing between elements
}

void UI::DrawUI(sf::RenderWindow& window, sf::Time dt, UI& ui, const Window& windowObj) {
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


    //SETTINGS GEAR ICON
    if (!ui.showClickMessage) {
        // Calculate gear properties
        float localscale = .75f;
        float gearRadius = CharacterSize * 0.6f * localscale;
        float toothWidth = CharacterSize * .25f * localscale;
        float toothLength = CharacterSize * 0.275f * localscale;
        
        // Position for the gear (center point)
        float gearCenterX = static_cast<float>(window.getSize().x) - 10.f * 1.5f - resetdiff;
        float gearCenterY = 20.0f * scale + gearRadius;
        
        // Draw gear teeth first (so circle draws on top)
        sf::RectangleShape& settingsIconTooth = ui.getSettingsIconTooth();
        settingsIconTooth.setFillColor(sf::Color::White);
        //settingsIconTooth.setOutlineColor(sf::Color::White);
        //settingsIconTooth.setOutlineThickness(CharacterSize * 0.05f);
        settingsIconTooth.setSize(sf::Vector2f(toothWidth, toothLength));
        // Set origin to center of the tooth for proper rotation
        settingsIconTooth.setOrigin(sf::Vector2f(toothWidth + CharacterSize * .4f , toothLength / 2.0f));
        
        // Draw 8 teeth around the circle
        for (int i = 0; i < 8; ++i) {
            sf::Angle angle = i * sf::degrees(45.0f); // 360/8 = 45 degrees
            settingsIconTooth.setRotation(angle);
            
            // Calculate tooth position on the circle's edge
            float angleRad = angle.asRadians();
            float toothX = gearCenterX + std::cos(angleRad);
            float toothY = gearCenterY + std::sin(angleRad);
            
            settingsIconTooth.setPosition(sf::Vector2f(toothX, toothY));
            window.draw(settingsIconTooth);
        }
        
        // Draw gear circle
        sf::CircleShape& settingsIconCircle = ui.getSettingsIconCircle();
        settingsIconCircle.setRadius(gearRadius * 0.6f); // Inner circle is smaller
        settingsIconCircle.setFillColor(sf::Color::Transparent);
        settingsIconCircle.setOutlineColor(sf::Color::White);
        settingsIconCircle.setOutlineThickness(CharacterSize * 0.2f * localscale);
        
        // Set origin to center of circle for easier positioning
        settingsIconCircle.setOrigin(sf::Vector2f(settingsIconCircle.getRadius(), settingsIconCircle.getRadius()));
        settingsIconCircle.setPosition(sf::Vector2f(gearCenterX, gearCenterY));
        
        window.draw(settingsIconCircle);
    }
    
    // Draw settings menu only if open
    if (ui.settingsMenuOpen) {
        ui.GenerateSettingsMenu(window, ui, windowObj);
    }


    // RESET BUTTON
    if (!ui.showClickMessage) {
        float localscale = .75f;
        float iconRadius = CharacterSize * 0.4f * localscale;

        // Calculate position for reset icon (to the left of the gear icon)
        float resetIconCenterX =static_cast<float>(window.getSize().x) - 10.f * 1.5f - resetdiff; // Position to the left of gear
        float resetIconCenterY = 100.0f * scale + iconRadius;

        



        sf::CircleShape& resetIconCircle = ui.getResetIconCircle();
        resetIconCircle.setRadius(iconRadius);
        resetIconCircle.setFillColor(sf::Color::Transparent);
        resetIconCircle.setOutlineColor(sf::Color::White);
        resetIconCircle.setOutlineThickness(CharacterSize * 0.15f * localscale);
        resetIconCircle.setOrigin(sf::Vector2f(resetIconCircle.getRadius(), resetIconCircle.getRadius()));
        resetIconCircle.setPosition(sf::Vector2f(resetIconCenterX, resetIconCenterY));
        window.draw(resetIconCircle);

		sf::RectangleShape& resetIconRectangle = ui.getResetIconRectangle();
		resetIconRectangle.setFillColor(sf::Color::Black);
		resetIconRectangle.setSize(sf::Vector2f(CharacterSize * .8f, CharacterSize * .5f));
		resetIconRectangle.setOrigin(sf::Vector2f(resetIconCircle.getRadius() * .6f, resetIconCircle.getRadius() * .5f));
        resetIconRectangle.setPosition(sf::Vector2f(resetIconCenterX + iconRadius * .5f, resetIconCenterY + iconRadius * .5f));
		//window.draw(resetIconRectangle);

        sf::ConvexShape& resetIconArrow = ui.getResetIconArrow();
        resetIconArrow.setPointCount(3);
        float arrowscale = .6f;
        resetIconArrow.setPoint(0, sf::Vector2f(0 * localscale * arrowscale * CharacterSize, 0 * localscale * arrowscale * CharacterSize));
        resetIconArrow.setPoint(1, sf::Vector2f(0.5 * localscale * arrowscale * CharacterSize, -1 * localscale * arrowscale * CharacterSize));
        resetIconArrow.setPoint(2, sf::Vector2f(-0.5 * localscale * arrowscale * CharacterSize, -1 * localscale * arrowscale * CharacterSize));
        resetIconArrow.setFillColor(sf::Color::White);
        resetIconArrow.setPosition(sf::Vector2f(resetIconCenterX - iconRadius + 2.9f, resetIconCenterY - iconRadius - 2.0f));
        resetIconArrow.setRotation(sf::degrees(200.0f));
        window.draw(resetIconArrow);

        //sf::Text resetSymbol{ arial };
        //resetSymbol.setString("Reset:↻");
        //resetSymbol.setFillColor(sf::Color::White);
        //resetSymbol.setCharacterSize(static_cast<unsigned int>(CharacterSize * 1.2f * localscale));
        //resetSymbol.setPosition(sf::Vector2f(resetIconCenterX - 500.f, resetIconCenterY));
        //window.draw(resetSymbol);


        // Start the reset text timer when button is pressed
        if (ui.resetButtonPressed) {
            ui.showResetText = true;
            ui.resetTextTimer = 0.0f;
            ui.resetButtonPressed = false;
        }

        // Update and display aircraft deleted text if active
        if (ui.showResetText) {
            ui.resetTextTimer += dt.asSeconds();

            if (ui.resetTextTimer >= ui.resetTextDuration) {
                ui.showResetText = false;
            }
            else {
                sf::Text resetText{ edges };
                resetText.setString("All aircraft deleted");
                resetText.setFillColor(sf::Color::White);
                resetText.setCharacterSize(static_cast<unsigned int>(CharacterSize * 3.0f));
                sf::FloatRect rtb = resetText.getLocalBounds();
                resetText.setOrigin(rtb.position + rtb.size / 2.0f);
                resetText.setPosition(sf::Vector2f(static_cast<float>(window.getSize().x) / 2.0f, static_cast<float>(window.getSize().y) / 2.0f));
                window.draw(resetText);
            }
        }
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