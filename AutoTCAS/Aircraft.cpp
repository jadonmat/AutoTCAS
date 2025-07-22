#include "Aircraft.h"

//Vector2i is used for a vector of ints
//Vector2f is used for a vector of floats
//etc

//Do not use SFML's angle class in setheadingangle, doesnt work with std trig functions

Aircraft::Aircraft() { ShapeScale = 0.26f; }//default constructor
Aircraft::~Aircraft() {}//deconstructor

//Getter and setters for ShapeScaling
void Aircraft::setShapeScale(float scale) {
    ShapeScale = scale;
}
float Aircraft::getShapeScale() const {
    return ShapeScale;
}

//update the aircrafts position over time
void Aircraft::update(sf::Time dt) {
    position.x += velocity.x * dt.asSeconds(); //convert dt to float from cf::Time
    position.y += velocity.y * dt.asSeconds();
}

void Aircraft::avoidCollision(int i, sf::RenderWindow& window, const std::vector<Aircraft*>& aircrafts, std::vector<std::vector<sf::ConvexShape>>& aircraftShapes,
    sf::Time dt, float smoothingfactor, float maxturnrate) {
    float deltaTime = dt.asSeconds();
    if (deltaTime <= 0.f) {
        return; // Skip if dt is invalid
    }

    // Find the closest aircraft
    float minDistance = warningrange; // Initialize to maximum detection range
    sf::Vector2f closestSeparation(0.f, 0.f);
    bool found = false;

    for (const auto& other : aircrafts) {
        if (other != this && DetectAircraft(other)) {
            float distance = std::hypot(other->getPosition().x - position.x, other->getPosition().y - position.y);
            if (distance > 0 && distance < minDistance) {
                minDistance = distance;
                closestSeparation = position - other->getPosition();
                found = true;
            }
        }
    }

    if (found) {
        // Normalize the separation vector
        float currentDistance = std::sqrt(closestSeparation.x * closestSeparation.x + closestSeparation.y * closestSeparation.y);
        if (currentDistance < 0.001f) {
            currentDistance = 0.001f;
        }
        if (std::abs(closestSeparation.x) < 0.001f && std::abs(closestSeparation.y) < 0.001f) {
            return; // Skip if separation is effectively zero
        }
        closestSeparation.x /= currentDistance;
        closestSeparation.y /= currentDistance;

        // Apply separation weight based on proximity
        float separationWeight = (warningrange - minDistance) / warningrange;
        closestSeparation.x *= separationWeight;
        closestSeparation.y *= separationWeight;

        // Calculate desired heading
        float desiredAngleRadians = std::atan2(closestSeparation.y, closestSeparation.x);
        float desiredAngleDegrees = desiredAngleRadians * (180.0f / 3.14f);

        // relative position and velocity for additional checks
        // 
        //sf::Vector2f relativePos = -closestSeparation; // other.getPosition() - position
        //sf::Vector2f relativeVelocity = other.getVelocity() - getVelocity();
        //float crossProduct = closestSeparation.x * relativePos.y - closestSeparation.y * relativePos.x;
        //float closingSpeed = relativeVelocity.x * closestSeparation.x + relativeVelocity.y * closestSeparation.y;

        float currentAngle = getHeadingAngle().asDegrees();
        float angleDiff = desiredAngleDegrees - currentAngle;

        // Normalize angle difference
        while (angleDiff > 180) {
            angleDiff -= 360;
        }
        while (angleDiff < -180) {
            angleDiff += 360;
        }

        // Apply smooth turning
        float smoothingFactor = smoothingfactor; // Base turn speed
        float maxTurnRate = maxturnrate; // Max degrees per second
        float angleChange = std::clamp(smoothingFactor * angleDiff * deltaTime,
            -maxTurnRate * deltaTime, maxTurnRate * deltaTime);
        float newAngle = currentAngle + angleChange;
        headingAngle = sf::degrees(newAngle);
        setHeadingAngle(newAngle);
        //std::cout << "Turn rate: " << angleChange / deltaTime << " deg/s, angleDiff: " << angleDiff << std::endl;


    }

    // Relate Aircraft and TCAS class
    bool collisionDetected = false;
    bool warningDetected = false;
    for (int j = 0; j < aircrafts.size(); ++j) {
        if (i != j && aircrafts[i]->DetectAircraft(aircrafts[j])) {
            warningDetected = true;
        }
        if (i != j && aircrafts[i]->DetectCollision(aircrafts[j])) {
            collisionDetected = true;
        }
    }
	// Update the color of the aircraft shapes based on detection status
    for (auto& shape : aircraftShapes[i]) {
        if (collisionDetected) {
            shape.setFillColor(sf::Color::Red);
        }
        else if (warningDetected) {
            shape.setFillColor(sf::Color{ 255,150,0 });
        }
        else {
            shape.setFillColor(sf::Color::Green);
        }

    // Draw the aircraft shapes with updated colors
    // with constant determination of positions and headings
        shape.setPosition(aircrafts[i]->getPosition());
        shape.setRotation(aircrafts[i]->getHeadingAngle() + sf::degrees(90));
        window.draw(shape);
    }
}