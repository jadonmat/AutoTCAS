#pragma once
#include "Radar.h"
#include <cmath>
// This class is going to be used for the sensor

class TCAS : public Radar {

public:

	TCAS();

	float getRange() const;

	bool DetectAircraft(const TCAS* otherAircraft);

	bool DetectCollision(const TCAS* otherAircraft);

protected:
	float range;
	float warningrange;
};
