#include "Engine.h"


Engine::Engine() : velocity(1, 1) {}

void Engine::setVelocity(sf::Vector2f vel) {
	velocity.x = vel.x;
	velocity.y = vel.y;
}

sf::Vector2f Engine::getVelocity() const {
	return velocity;
}