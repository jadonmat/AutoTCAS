#pragma once
#include "Radar.h"
#include <cmath>
// This class is going to be used for the sensor

class TCAS : public Radar {

public:

	TCAS() { range = 100.f; }

	float getRange() const {
		return range;
	}

	virtual bool detectAircraft(const TCAS& otherAircraft) {

		float distance = sqrt(pow(otherAircraft.getPosition().x - position.x, 2) +
			pow(otherAircraft.getPosition().y - position.y, 2));
		return distance < range;
	}

protected:
	float range;
};
