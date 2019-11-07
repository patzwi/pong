// Ball.hpp
// Interface & definition for the Ball class.
// Patrick Zwierzynski

#ifndef Ball_hpp
#define Ball_hpp

#include <SFML/Graphics.hpp>
#include <stdlib.h>

class Ball {
    // Describe Ball CONSTANTS
    const int BALL_INIT_SIZE {15};
    const int BALL_INIT_SPD  {0};
    // Describes the velocity of the Ball
    sf::Vector2f vel{(float)BALL_INIT_SPD,
                     (float)BALL_INIT_SPD};
    // Describes the graphical shape of the ball
    sf::CircleShape circle{(float)BALL_INIT_SIZE};
public:
    // Construct the ball w/ random velocity
    Ball (sf::Vector2f& new_pos);
    
    // DEBUG CONSTRUCTOR
    Ball (sf::Vector2f& new_vel, sf::Vector2f& new_pos);
    
    // Get Graphical SFML Ball object
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
    
    // Get Radius
    float getRadius();
    
    // Set Color
    void setColor(const sf::Color& c);
};

#endif /* Ball_hpp */
