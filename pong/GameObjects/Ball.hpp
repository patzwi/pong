// Ball.hpp
// Interface & definition for the Ball class.
// Patrick Zwierzynski

#ifndef Ball_hpp
#define Ball_hpp
#define BALL_INIT_SIZE 15
#define BALL_INIT_VEL 0

#include <SFML/Graphics.hpp>
#include <stdlib.h>

class Ball {
    // Describes the velocity of the Ball
    sf::Vector2f vel{BALL_INIT_VEL, BALL_INIT_VEL};
    // Describes the graphical shape of the ball
    sf::CircleShape circle{BALL_INIT_SIZE};
public:
    // Construct the ball
    Ball (sf::Vector2f& new_vel, sf::Vector2f& new_pos);
    
    // Get Graphical Sf object
    const sf::CircleShape& getGraphic();
    
    // Get Velocity
    const sf::Vector2f& getVelocity();
    
    // Set Velocity
    void setVelocity(const sf::Vector2f& new_vel);
    
    // Get Position
    const sf::Vector2f& getPosition();
    
    // Set Position
    void setPosition(const sf::Vector2f& new_pos);
    
    // Update motion
    void dtUpdate();
    
    // Horizontal deflection
    void xDeflect();
    
    // Vertical deflection
    void yDeflect();
};

#endif /* Ball_hpp */
