#include "TCAS.h"

TCAS::TCAS() { range = 50.f; warningrange = 90.f; }

float TCAS::getRange() const {
	return range;
}

bool TCAS::DetectAircraft(const TCAS* otherAircraft) {
	float distance = sqrt(powf(otherAircraft->getPosition().x - position.x, 2.f) +
		powf(otherAircraft->getPosition().y - position.y, 2));
	return distance < warningrange;
}

bool TCAS::DetectCollision(const TCAS* otherAircraft) {
    float dx = otherAircraft->getPosition().x - position.x;
    float dy = otherAircraft->getPosition().y - position.y;
    float distanceSquared = dx * dx + dy * dy;
    return distanceSquared < (range * range);
}