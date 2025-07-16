#pragma once
#include "Radar.h"
#include <cmath>
// This class is going to be used for the sensor

class TCAS : public Radar {

public:

	TCAS() { range = 50.f; warningrange = 90.f; }

	float getRange() const {
		return range;
	}

	bool DetectAircraft(const TCAS* otherAircraft) {
		float distance = sqrt(powf(otherAircraft->getPosition().x - position.x, 2.f) +
			powf(otherAircraft->getPosition().y - position.y, 2));
		return distance < warningrange;
	}

	bool DetectCollision(const TCAS* otherAircraft) {
		float distance = sqrt(pow(otherAircraft->getPosition().x - position.x, 2.f) +
			pow(otherAircraft->getPosition().y - position.y, 2.f));
		return distance < range;

	}

protected:
	float range;
	float warningrange;
};
