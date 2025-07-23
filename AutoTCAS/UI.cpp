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
    showTooCloseMessage = false;
    tooCloseTimer = 0.0f;
    tooCloseDisplayDuration = 2.0f; // Show for 2 seconds
}

sf::Font UI::getedgesFont() const {
    sf::Font edgesFont("Fonts/Edges.ttf");
    return edgesFont;
}

sf::Font UI::getpixellariFont() const {
	sf::Font pixellariFont("Fonts/Pixellari.ttf");
	return pixellariFont;
}

sf::Text& UI::getResetButton() {
    return reset; 
}

sf::Text& UI::getFPSDisplay() {
    return fpsText; 
}

void UI::FPSDisplay(sf::Time dt, sf::Text& fpsText) {
    //FPS display
    frameTime += dt.asSeconds();
    frameCount++;
    if (frameTime >= 1.0f) {
        float fps = frameCount / frameTime;
        fpsText.setString("FPS: " + std::to_string(static_cast<int>(fps)));
        frameTime = 0.0f;
        frameCount = 0.0f;
    }
}

sf::Text& UI::getClickText() {
    return clickText; 
}

sf::Text& UI::getTooCloseMessage() {
    return TooClose;
}

// Add this method after the other getter methods
void UI::showTooCloseMessageFor(float duration) {
    showTooCloseMessage = true;
    tooCloseTimer = 0.0f;
    tooCloseDisplayDuration = duration;
}

// handles differnet buttons with texttype
void UI::TextUpdate(sf::Text& text, sf::RenderWindow& window, TextType type) const {
    sf::Font font = getedgesFont();
    float CharacterSize = 0.0f;
    float CharacterSizeFPS = 0.0f;
    sf::VideoMode CurrentDesktopMode = sf::VideoMode::getDesktopMode();
    //720p case
    if (CurrentDesktopMode.size.x == 1280u && CurrentDesktopMode.size.y == 720u) {
        CharacterSize = 20.0f;
        CharacterSizeFPS = 10.0f;
        //cout << "1280x720" << endl;
    }
    //1080p case
    else if (CurrentDesktopMode.size.x == 1920u && CurrentDesktopMode.size.y == 1080u) {
        CharacterSize = 25.0f;
        CharacterSizeFPS = 12.5f;
        //cout << "1920x1080" << endl;
    }
    //1440p case
    else if (CurrentDesktopMode.size.x == 2560u && CurrentDesktopMode.size.y == 1440u) {
        CharacterSize = 30.0f;
        CharacterSizeFPS = 15.0f;
        //cout << "2560x1440" << endl;
    }
    // 3.5k to 4k case
    else if (CurrentDesktopMode.size.x >= 3456u && CurrentDesktopMode.size.x <= 3840u && CurrentDesktopMode.size.y == 2160u) {
        CharacterSize = 50.0f;
        CharacterSizeFPS = 27.5f;
        //cout << "3456x1440" << endl;

    }
    // 4k
    else {
        cout << "ERROR: Scaling does not match up" << endl;
        int textamt = 11;
        vector<sf::Text> ErrorTexts(static_cast<size_t>(textamt), sf::Text(font));

        sf::Clock errorClock;
        float errorTime = 30.0f; // seconds

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
        text.setCharacterSize(static_cast<unsigned int>(CharacterSize + 20.f));
        sf::FloatRect bounds = text.getLocalBounds();
        sf::Vector2f center = bounds.getCenter();
        text.setPosition(sf::Vector2f(static_cast<float>(window.getSize().x) / 2.0f - center.x, static_cast<float>(window.getSize().y) / 2.0f - center.y));
    }
    else if (type == TextType::TooClose) {
        text.setString("TOO CLOSE");
        text.setFillColor(sf::Color::White);
        text.setCharacterSize(static_cast<unsigned int>(CharacterSize- 30.0f));
        sf::FloatRect bounds = text.getLocalBounds();
        sf::Vector2f center = bounds.getCenter();
        text.setPosition(sf::Vector2f(static_cast<float>(window.getSize().x) / 2.0f - center.x, static_cast<float>(window.getSize().y) / 2.0f - center.y));
	}
    else {
        cout << "ERROR: TextUpdate type does not match up" << endl;
	}
}

void UI::InitializeUI(sf::RenderWindow& window, UI& ui) {
    // Settings BUTTON

    // Reset BUTTON 
    sf::Text reset = ui.getResetButton();
    ui.TextUpdate(reset, window, UI::TextType::Reset);

    //FPS display
    sf::Text fpsText = ui.getFPSDisplay();
    ui.TextUpdate(fpsText, window, UI::TextType::FPS);

    // Clicktext display
    sf::Text clickText = ui.getClickText();
    ui.TextUpdate(clickText, window, UI::TextType::Click);

    //Too close display
	sf::Text tooCloseText = ui.getClickText();
	ui.TextUpdate(tooCloseText, window, UI::TextType::TooClose);
}

void UI::DrawAndOrAnimate(sf::RenderWindow& window, sf::Time dt, UI& ui) {
    // Handle Too Close message timing
    if (showTooCloseMessage) {
        tooCloseTimer += dt.asSeconds();
        if (tooCloseTimer >= tooCloseDisplayDuration) {
            showTooCloseMessage = false;
            tooCloseTimer = 0.0f;
        }
    }

    // animate click message
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
        // Always set origin from the local bounds to keep it centered.
        clickText.setOrigin(clickText.getLocalBounds().position + clickText.getLocalBounds().size / 2.0f);
        clickText.setPosition(sf::Vector2f(static_cast<float>(window.getSize().x) / 2.0f, static_cast<float>(window.getSize().y) / 2.0f));

        // Optional: draw a semi-transparent overlay.
        sf::RectangleShape overlay(sf::Vector2f(static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y)));
        overlay.setFillColor(sf::Color(0, 0, 0, 128));
        window.draw(overlay);
        window.draw(clickText);
    }


    if (!ui.showClickMessage) {
		ui.TextUpdate(ui.reset, window, TextType::Reset);
		ui.FPSDisplay(dt, ui.fpsText);
		ui.TextUpdate(ui.fpsText, window, TextType::FPS);

        window.draw(ui.reset);
        window.draw(ui.fpsText);
    }
    
    // Draw Too Close message if active
    if (showTooCloseMessage) {
        ui.TextUpdate(ui.TooClose, window, TextType::TooClose);

        // Optional: Add a semi-transparent red overlay for emphasis
        sf::RectangleShape overlay(sf::Vector2f(static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y)));
        overlay.setFillColor(sf::Color(255, 0, 0, 64)); // Red with low alpha
        window.draw(overlay);
        window.draw(ui.TooClose);
    }
}