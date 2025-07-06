#pragma once
#include <SFML/Graphics.hpp>

class Engine {
public:
	Engine() : velocity(2, 2) {}

	void setVelocity(sf::Vector2f vel) {
		velocity.x = vel.x;
		velocity.y = vel.y;
	}

	sf::Vector2f getVelocity() const {
		return velocity;
	}


protected:
	sf::Vector2f velocity;

};
