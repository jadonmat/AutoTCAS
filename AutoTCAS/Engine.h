#pragma once
#include <SFML/Graphics.hpp>

class Engine {
public:
	Engine();

	void setVelocity(sf::Vector2f vel);

	sf::Vector2f getVelocity() const;


protected:
	sf::Vector2f velocity;

};
