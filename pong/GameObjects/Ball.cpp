// Ball.cpp
// Ball class implementation
// Patrick Zwierzynski

#include "Ball.hpp"

Ball::Ball (sf::Vector2f& new_pos) {
    vel = sf::Vector2f ((rand() % 5) + 5, (rand() % 5) + 5);
//    vel = sf::Vector2f (10, 0);
    circle.setPosition(new_pos);
    circle.setFillColor(sf::Color(rand() % 255, rand() % 255, rand() % 255));
}

// DEBUG Ball constructor
Ball::Ball (sf::Vector2f& new_vel, sf::Vector2f& new_pos) {
    vel = new_vel;
    circle.setPosition(new_pos);
    circle.setFillColor(sf::Color(rand() % 255, rand() % 255, rand() % 255));
}

// Get Graphical Sf object
const sf::CircleShape& Ball::getGraphic() { return circle; }

// Get Velocity
const sf::Vector2f& Ball::getVelocity() { return vel; }

// Set Velocity
void Ball::setVelocity(const sf::Vector2f& new_vel) { vel = new_vel; }

// Get Position
const sf::Vector2f& Ball::getPosition() { return circle.getPosition(); }

// Set Position
void Ball::setPosition(const sf::Vector2f& new_pos) { circle.setPosition(new_pos); }

// Update motion
void Ball::dtUpdate() { circle.move(vel.x, vel.y); }

// Horizontal deflection
void Ball::xDeflect() {
    sf::Vector2f new_vel (-vel.x, vel.y);
    vel = new_vel;
}

// Vertical deflection
void Ball::yDeflect() {
    sf::Vector2f new_vel (vel.x, -vel.y);
    vel = new_vel;
}

// Get radius
float Ball::getRadius() { return circle.getRadius(); }
