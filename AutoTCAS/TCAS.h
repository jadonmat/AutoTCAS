#pragma once
#include "Radar.h"
#include <cmath>
// This class is going to be used for the sensor

class TCAS : public Radar {

public:

	TCAS() { range = 45.f; warningrange = 80.f; }

	float getRange() const {
		return range;
	}

	bool DetectAircraft(const TCAS& otherAircraft) {
		float distance = sqrt(pow(otherAircraft.getPosition().x - position.x, 2) +
			pow(otherAircraft.getPosition().y - position.y, 2));
		return distance < warningrange;
	}

	bool DetectCollision(const TCAS& otherAircraft) {
		float distance = sqrt(pow(otherAircraft.getPosition().x - position.x, 2) +
			pow(otherAircraft.getPosition().y - position.y, 2));
		return distance < range;

	}

protected:
	float range;
	float warningrange;
};
